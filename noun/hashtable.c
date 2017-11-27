/* g/h.c
**
*/
#include "all.h"

c3_o RECLAIMING = c3n;

static void
_ch_slot_put(u3h_root*, u3h_slot* sot_w, u3_noun kev, c3_w lef_w, c3_w rem_w, c3_w* use_w);

static c3_o
_ch_trim_slot(u3h_root* har_u, u3h_slot *sot_w, c3_w lef_w, c3_w rem_w);

c3_w
_ch_skip_slot(c3_w mug_w, c3_w lef_w);

/* u3h_new_cache(): create hashtable with bounded size.
*/
u3p(u3h_root)
u3h_new_cache(c3_w max_w)
{
  u3h_root*     har_u = u3a_walloc(c3_wiseof(u3h_root));
  u3p(u3h_root) har_p = u3of(u3h_root, har_u);
  c3_w        i_w;

  har_u->max_w       = max_w;
  har_u->use_w       = 0;
  har_u->arm_u.mug_w = 0;
  har_u->arm_u.inx_w = 0;
  har_u->arm_u.buc_o = c3n;

  for ( i_w = 0; i_w < 64; i_w++ ) {
    har_u->sot_w[i_w] = 0;
  }
  return har_p;
}

/* u3h_new(): create hashtable.
*/
u3p(u3h_root)
u3h_new(void)
{
  return u3h_new_cache(0);
}

/* _ch_popcount(): number of bits set in word.  A standard intrinsic.
*/
static c3_w
_ch_popcount(c3_w num_w)
{
  return __builtin_popcount(num_w);
}

/* _ch_buck_new(): create new, empty bucket.
*/
static u3h_buck*
_ch_buck_new(void)
{
  u3h_buck* hab_u = u3a_walloc(c3_wiseof(u3h_buck));

  hab_u->len_w = 0;
  return hab_u;
}

/* _ch_node_new(): create new, empty node.
*/
static u3h_node*
_ch_node_new(void)
{
  u3h_node* han_u = u3a_walloc(c3_wiseof(u3h_node));

  han_u->map_w = 0;
  return han_u;
}

/* _ch_some_new(): create node or bucket.
*/
static void*
_ch_some_new(c3_w lef_w)
{
  if ( 0 == lef_w ) {
    return _ch_buck_new();
  }
  else {
    return _ch_node_new();
  }
}

/* _ch_node_add(): add to node.
*/
static u3h_node*
_ch_node_add(u3h_root* har_u, u3h_node* han_u, c3_w lef_w, c3_w rem_w, u3_noun kev, c3_w *use_w)
{
  c3_w bit_w, inx_w, map_w, i_w;

  lef_w -= 5;
  bit_w = (rem_w >> lef_w);
  rem_w = (rem_w & ((1 << lef_w) - 1));
  map_w = han_u->map_w;
  inx_w = _ch_popcount(map_w & ((1 << bit_w) - 1));

  if ( map_w & (1 << bit_w) ) {
    _ch_slot_put(har_u, &(han_u->sot_w[inx_w]), kev, lef_w, rem_w, use_w);
    return han_u;
  }
  else {
    //  nothing was at this slot.
    //  Optimize: use u3a_wealloc.
    //
    c3_w      len_w = _ch_popcount(map_w);
    u3h_node* nah_u = u3a_walloc(c3_wiseof(u3h_node) +
                                 ((len_w + 1) * c3_wiseof(u3h_slot)));
    nah_u->map_w = han_u->map_w | (1 << bit_w);

    for ( i_w = 0; i_w < inx_w; i_w++ ) {
      nah_u->sot_w[i_w] = han_u->sot_w[i_w];
    }
    nah_u->sot_w[inx_w] = u3h_noun_be_warm(u3h_noun_to_slot(kev));
    for ( i_w = inx_w; i_w < len_w; i_w++ ) {
      nah_u->sot_w[i_w + 1] = han_u->sot_w[i_w];
    }

    u3a_wfree(han_u);
    *use_w += 1;
    return nah_u;
  }
}

/* ch_buck_add(): add to bucket.
*/
static u3h_buck*
_ch_buck_add(u3h_buck* hab_u, u3_noun kev, c3_w *use_w)
{
  c3_w i_w;

  //  if our key is equal to any of the existing keys in the bucket,
  //  then replace that key-value pair with kev.
  //
  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    u3_noun kov = u3h_slot_to_noun(hab_u->sot_w[i_w]);
    if ( c3y == u3r_sing(u3h(kev), u3h(kov)) ) {
      u3a_lose(kov);
      hab_u->sot_w[i_w] = u3h_noun_to_slot(kev);

      return hab_u;
    }
  }

  //  create mutant bucket with added key-value pair.
  {
    c3_w len_w      = hab_u->len_w;
    u3h_buck* bah_u = u3a_walloc(c3_wiseof(u3h_buck) +
                                 (len_w + 1) * c3_wiseof(u3h_slot));

    bah_u->len_w    = len_w + 1;
    bah_u->sot_w[0] = u3h_noun_to_slot(kev);

    // Optimize: use u3a_wealloc().
    //
    for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
      bah_u->sot_w[i_w + 1] = hab_u->sot_w[i_w];
    }

    u3a_wfree(hab_u);
    *use_w += 1;
    return bah_u;
  }
}

/* _ch_some_add(): add to node or bucket.
*/
static void*
_ch_some_add(u3h_root* har_u, void* han_v, c3_w lef_w, c3_w rem_w, u3_noun kev, c3_w *use_w)
{
  if ( 0 == lef_w ) {
    return _ch_buck_add((u3h_buck*)han_v, kev, use_w);
  }
  else return _ch_node_add(har_u, (u3h_node*)han_v, lef_w, rem_w, kev, use_w);
}

/* _ch_slot_put(): store a key-value pair in a u3h_slot (root or node) 
*/
static void
_ch_slot_put(u3h_root* har_u, u3h_slot* sot_w, u3_noun kev, c3_w lef_w, c3_w rem_w, c3_w* use_w)
{
  if ( c3y == u3h_slot_is_null(*sot_w) ) {
    *sot_w = u3h_noun_be_warm(u3h_noun_to_slot(kev));
    *use_w += 1;
  }
  else if ( c3y == u3h_slot_is_noun(*sot_w) ) {
    u3_noun kov = u3h_slot_to_noun(*sot_w);
    if ( c3y == u3r_sing(u3h(kev), u3h(kov)) ) {
      *sot_w = u3h_noun_be_warm(u3h_noun_to_slot(kev));
      u3z(kov);
    }
    else {
      c3_w  rom_w = u3r_mug(u3h(kov)) & ((1 << lef_w) - 1);
      void* hav_v = _ch_some_new(lef_w);
      void* hav_2, *hav_3;

      *use_w -= 1;// take one out, add two
      hav_2 = _ch_some_add(har_u, hav_v, lef_w, rom_w, kov, use_w);
      hav_3 = _ch_some_add(har_u, hav_2, lef_w, rem_w, kev, use_w);
      *sot_w = u3h_node_to_slot(hav_3);

      if ( c3y == RECLAIMING ) {
        fprintf(stderr,
          "slot_put kev->node lef_w %02d hav_1 %08x hav_2 %08x hav_3 %08x\r\n",
          lef_w, hav_v, hav_2, hav_3);
      }
    }
  }
  else {
    void* old_v, *hav_v;
    c3_assert( c3y == u3h_slot_is_node(*sot_w) );

    old_v = u3h_slot_to_node(*sot_w);
    hav_v = _ch_some_add(har_u, old_v, lef_w, rem_w, kev, use_w);
    *sot_w = u3h_node_to_slot(hav_v);

    if ( c3y == RECLAIMING ) {
      fprintf(stderr,
        "slot_put node->node lef_w %02d old_v %08x hav_v %08x\r\n",
        lef_w, old_v, hav_v);
    }
  }
}

/* _ch_trim_node(): trim one entry from a node slot or its children
*/
static c3_o
_ch_trim_node(u3h_root* har_u, u3h_slot* sot_w, c3_w lef_w, c3_w rem_w)
{
  c3_w bit_w, map_w, inx_w;
  u3h_slot* tos_w;
  u3h_node* han_u;

  han_u = (u3h_node*) u3h_slot_to_node(*sot_w);

  c3_assert(c3y == u3h_slot_is_node(*sot_w));
  c3_assert(0 < _ch_popcount(han_u->map_w));
  c3_assert(!((1 == _ch_popcount(han_u->map_w))
              && (c3y == u3h_slot_is_noun(han_u->sot_w[0]))));
  c3_assert(0 != han_u->sot_w[0]);
 
  lef_w -= 5;
  bit_w = (rem_w >> lef_w);
  map_w = han_u->map_w;

  while ( 0 == (map_w & (1 << bit_w)) ) {
    bit_w++;
    har_u->arm_u.mug_w = _ch_skip_slot(har_u->arm_u.mug_w, lef_w);
    
    if ( bit_w > 31 ) {
      return c3n;
    }
  }

  rem_w = (rem_w & ((1 << lef_w) - 1));
  inx_w = _ch_popcount(map_w & ((1 << bit_w) - 1));
  tos_w = &(han_u->sot_w[inx_w]);

  if ( c3n == _ch_trim_slot(har_u, tos_w, lef_w, rem_w) ) {
    // nothing trimmed
    return c3n;
  }
  else if ( 0 != *tos_w ) {
    // something trimmed, but slot still has value
    
    //  shrink!
    if ( c3y == u3h_slot_is_noun(*tos_w) && (_ch_popcount(map_w) == 1) ) {
      *sot_w = *tos_w;
      fprintf(stderr,
          "FREE %08x lef_w %02d raising key-value pair from sub-slot\r\n",
          han_u, lef_w);
      u3a_wfree(han_u);
    }

    return c3y;
  }
  else {
    // shrink!
    c3_w i_w, len_w = _ch_popcount(map_w);
    u3h_slot sur_w;

    //  if we only contained a single item, then that item must be a node.
    //  if a node contains only key-value pairs (not another node or bucket),
    //  then it must contain at least two of them. that means if after running
    //  _ch_trim_slot(), tos_w got zeroed out, then that should only have
    //  happened if that wasn't our only slot. if it *was* our only slot and
    //  it got zeroed out, then it must have contained only one key-value
    //  pair. therefore, we should never reach this case if we started with
    //  only one slot.
    c3_assert(1 != len_w);

    if ( 2 == len_w && c3y == u3h_slot_is_noun(
          sur_w = han_u->sot_w[ ( 0 == inx_w )? 1 : 0 ]) ) {

      // raise key-value pair into self
      *sot_w = sur_w;
      fprintf(stderr,
          "FREE %08x lef_w %02d raising key-value pair from doubleton\r\n",
          han_u, lef_w);
      u3a_wfree(han_u);
    }
    else {
      // shrink node in place; don't reallocate, we could be low on memory
      //
      han_u->map_w = han_u->map_w & ~(1 << bit_w);

      for ( i_w = inx_w; i_w < (len_w - 1); i_w++ ) {
        han_u->sot_w[i_w] = han_u->sot_w[i_w + 1];
      }
      //  leave the last entry, since nothing points to it and we're not
      //  shrinking the box containing this node anyway. We could do:
      //  han_u->sot_w[len_w - 1] = 0;
    }
    return c3y;
  }
}

/* _ch_trim_buck(): trim one entry from a bucket slot
*/
static c3_o
_ch_trim_buck(u3h_root* har_u, u3h_slot* sot_w)
{
  c3_w i_w, len_w;
  u3h_buck* hab_u;

  c3_assert(c3y == u3h_slot_is_node(*sot_w));
  hab_u = u3h_slot_to_node(*sot_w);

  for ( har_u->arm_u.buc_o = c3y, len_w = hab_u->len_w; 
        har_u->arm_u.inx_w < len_w;
        har_u->arm_u.inx_w += 1 )
  {
    u3h_slot* tos_w = &(hab_u->sot_w[har_u->arm_u.inx_w]);
    if ( c3y == _ch_trim_slot(har_u, tos_w, 0, 0) ) {
      if ( 2 == len_w ) {
        // 2 things in bucket: pick the other and promote
        //
        *sot_w = hab_u->sot_w[ (0 == har_u->arm_u.inx_w) ? 1 : 0 ];
        u3a_wfree(hab_u);
      }
      else {
        // shrink bucket in place; don't reallocate, we could be low on memory
        //
        hab_u->len_w = len_w - 1;

        for ( i_w = har_u->arm_u.inx_w; i_w < (len_w - 1); ++i_w ) {
          hab_u->sot_w[i_w] = hab_u->sot_w[i_w + 1];
        }
      }
      return c3y;
    }
  }

  har_u->arm_u.mug_w = (har_u->arm_u.mug_w + 1) & 0x7FFFFFFF; // modulo 2^31
  har_u->arm_u.inx_w = 0;
  har_u->arm_u.buc_o = c3n;
  return c3n;
}

/* _ch_trim_some(): trim one entry from a bucket or node slot
*/
static c3_o
_ch_trim_some(u3h_root* har_u, u3h_slot* sot_w, c3_w lef_w, c3_w rem_w)
{
  if ( 0 == lef_w ) {
    return _ch_trim_buck(har_u, sot_w);
  }
  else {
    return _ch_trim_node(har_u, sot_w, lef_w, rem_w);
  }
}

/* _ch_skip_slot(): increment arm over hash prefix.
*/
c3_w
_ch_skip_slot(c3_w mug_w, c3_w lef_w)
{
  c3_w hig_w = mug_w >> lef_w;
  c3_w new_w = (hig_w + 1) & ((1 << (31 - lef_w)) - 1); // modulo 2^(31 - lef_w)
  return new_w << lef_w;
}

/* _ch_trim_slot(): trim one entry from a slot
*/
static c3_o
_ch_trim_slot(u3h_root* har_u, u3h_slot *sot_w, c3_w lef_w, c3_w rem_w)
{
  if ( _(u3h_slot_is_null(*sot_w)) ) {
    c3_assert(25 == lef_w);  //  null slots should only exist in the root.
    har_u->arm_u.mug_w = _ch_skip_slot(har_u->arm_u.mug_w, lef_w);
    return c3n;
  }
  else if ( _(u3h_slot_is_node(*sot_w)) ) {
    return _ch_trim_some(har_u, sot_w, lef_w, rem_w);
  }
  else {
    // this is a key-value pair
    u3_noun kev = u3h_slot_to_noun(*sot_w);
    c3_w hav_w = u3r_mug(u3h(kev)),
         luk_w = har_u->arm_u.mug_w;
 
    if ( luk_w < hav_w ) {
      har_u->arm_u.mug_w = hav_w;
      return c3n;
    }
    else if ( luk_w > hav_w ) {
      har_u->arm_u.mug_w = _ch_skip_slot(har_u->arm_u.mug_w, lef_w);
      return c3n;
    }
    else if ( _(u3h_slot_is_warm(*sot_w)) ) {
      *sot_w = u3h_noun_be_cold(*sot_w);
      if ( c3n == har_u->arm_u.buc_o ) {
        har_u->arm_u.mug_w = (har_u->arm_u.mug_w + 1) & 0x7FFFFFFF; // modulo 2^31
      }
      return c3n;
    }
    else {
      c3_assert(c3y == u3h_slot_is_cold(*sot_w));
 
      u3_noun kev = u3h_slot_to_noun(*sot_w);
 
      *sot_w = 0;
      u3z(kev);
 
      har_u->arm_u.mug_w = _ch_skip_slot(har_u->arm_u.mug_w, lef_w);
      return c3y;
    }
  }
}

/* _ch_trim_root(): trim one entry from a hashtable
*/
static c3_o
_ch_trim_root(u3h_root* har_u)
{
  c3_w      mug_w = har_u->arm_u.mug_w;
  c3_w      inx_w = mug_w >> 25; // 6 bits
  c3_w      rem_w = mug_w & ((1 << 25) - 1);
  u3h_slot* sot_w = &(har_u->sot_w[inx_w]);
  
  return _ch_trim_slot(har_u, sot_w, 25, rem_w);
}

/* u3h_trim_to(): trim to n key-value pairs
*/
void
u3h_trim_to(u3p(u3h_root) har_p, c3_w n_w)
{
  u3h_root* har_u = u3to(u3h_root, har_p);

  while ( har_u->use_w > n_w ) {
    if ( c3y == _ch_trim_root(har_u) ) {
      har_u->use_w -= 1;
    }
  }

#if 1
  u3h_sane(har_p);
#endif
}

/* u3h_put(): insert in hashtable.
**
** `key` is RETAINED; `val` is transferred.
*/
void
u3h_put(u3p(u3h_root) har_p, u3_noun key, u3_noun val)
{
  u3h_root*   har_u = u3to(u3h_root, har_p);
  u3_noun     kev   = u3nc(u3k(key), val);
  c3_w        mug_w = u3r_mug(key);
  c3_w        inx_w = (mug_w >> 25);  //  6 bits
  c3_w        rem_w = (mug_w & ((1 << 25) - 1));

  c3_w use_w = har_u->use_w;

  _ch_slot_put(har_u, &(har_u->sot_w[inx_w]), kev, 25, rem_w, &(har_u->use_w));

  if ( c3y == RECLAIMING ) {
    if ( _(u3h_slot_is_node(har_u->sot_w[inx_w])) ) {
      _ch_node_sane(u3h_slot_to_node(har_u->sot_w[inx_w]), 25);
    }
  }

  c3_assert((har_u->use_w == use_w) || (har_u->use_w == use_w + 1));

  if ( har_u->max_w > 0 ) {
    u3h_trim_to(har_p, har_u->max_w);
  }
}

/* _ch_buck_hum(): read in bucket.
*/
static c3_o
_ch_buck_hum(u3h_buck* hab_u, c3_w mug_w)
{
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    if ( mug_w == u3r_mug(u3h(u3h_slot_to_noun(hab_u->sot_w[i_w]))) ) {
      return c3y;
    }
  }
  return c3n;
}

/* _ch_node_hum(): read in node.
*/
static c3_o
_ch_node_hum(u3h_node* han_u, c3_w lef_w, c3_w rem_w, c3_w mug_w)
{
  c3_w bit_w, map_w;

  lef_w -= 5;
  bit_w = (rem_w >> lef_w);
  rem_w = (rem_w & ((1 << lef_w) - 1));
  map_w = han_u->map_w;

  if ( !(map_w & (1 << bit_w)) ) {
    return c3n;
  }
  else {
    c3_w inx_w = _ch_popcount(map_w & ((1 << bit_w) - 1));
    c3_w sot_w = han_u->sot_w[inx_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      if ( mug_w == u3r_mug(u3h(kev)) ) {
        return c3y;
      }
      else {
        return c3n;
      }
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        return _ch_buck_hum(hav_v, mug_w);
      }
      else return _ch_node_hum(hav_v, lef_w, rem_w, mug_w);
    }
  }
}

/* u3h_hum(): check presence in hashtable.
**
** `key` is RETAINED.
*/
c3_o
u3h_hum(u3p(u3h_root) har_p, c3_w mug_w)
{
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w        inx_w = (mug_w >> 25);
  c3_w        rem_w = (mug_w & ((1 << 25) - 1));
  c3_w        sot_w = har_u->sot_w[inx_w];

  if ( _(u3h_slot_is_null(sot_w)) ) {
    return c3n;
  }
  else if ( _(u3h_slot_is_noun(sot_w)) ) {
    u3_noun kev = u3h_slot_to_noun(sot_w);

    if ( mug_w == u3r_mug(u3h(kev)) ) {
      return c3y;
    }
    else {
      return c3n;
    }
  }
  else {
    u3h_node* han_u = u3h_slot_to_node(sot_w);

    return _ch_node_hum(han_u, 25, rem_w, mug_w);
  }
}

/* _ch_buck_git(): read in bucket.
*/
static u3_weak
_ch_buck_git(u3h_buck* hab_u, u3_noun key)
{
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    u3_noun kev = u3h_slot_to_noun(hab_u->sot_w[i_w]);
    if ( _(u3r_sing(key, u3h(kev))) ) {
      return u3t(kev);
    }
  }
  return u3_none;
}

/* _ch_node_git(): read in node.
*/
static u3_weak
_ch_node_git(u3h_node* han_u, c3_w lef_w, c3_w rem_w, u3_noun key)
{
  c3_w bit_w, map_w;

  lef_w -= 5;
  bit_w = (rem_w >> lef_w);
  rem_w = (rem_w & ((1 << lef_w) - 1));
  map_w = han_u->map_w;

  if ( !(map_w & (1 << bit_w)) ) {
    return u3_none;
  }
  else {
    c3_w inx_w = _ch_popcount(map_w & ((1 << bit_w) - 1));
    c3_w sot_w = han_u->sot_w[inx_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      if ( _(u3r_sing(key, u3h(kev))) ) {
        return u3t(kev);
      }
      else {
        return u3_none;
      }
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        return _ch_buck_git(hav_v, key);
      }
      else return _ch_node_git(hav_v, lef_w, rem_w, key);
    }
  }
}

/* u3h_git(): read from hashtable.
**
** `key` is RETAINED; result is RETAINED.
*/
u3_weak
u3h_git(u3p(u3h_root) har_p, u3_noun key)
{
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w      mug_w = u3r_mug(key);
  c3_w      inx_w = (mug_w >> 25);
  c3_w      rem_w = (mug_w & ((1 << 25) - 1));
  c3_w      sot_w = har_u->sot_w[inx_w];

  if ( _(u3h_slot_is_null(sot_w)) ) {
    return u3_none;
  }
  else if ( _(u3h_slot_is_noun(sot_w)) ) {
    u3_noun kev = u3h_slot_to_noun(sot_w);

    if ( _(u3r_sing(key, u3h(kev))) ) {
      har_u->sot_w[inx_w] = u3h_noun_be_warm(sot_w);
      return u3t(kev);
    }
    else {
      return u3_none;
    }
  }
  else {
    u3h_node* han_u = u3h_slot_to_node(sot_w);

    return _ch_node_git(han_u, 25, rem_w, key);
  }
}

/* u3h_get(): read from hashtable, incrementing refcount.
**
** `key` is RETAINED; result is PRODUCED.
*/
u3_weak
u3h_get(u3p(u3h_root) har_p, u3_noun key)
{
  u3_noun pro = u3h_git(har_p, key);

  if ( u3_none != pro ) {
    u3a_gain(pro);
  }
  return pro;
}

/* _ch_buck_gut(): read in bucket, unifying key nouns.
*/
static u3_weak
_ch_buck_gut(u3h_buck* hab_u, u3_noun key)
{
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    u3_noun kev = u3h_slot_to_noun(hab_u->sot_w[i_w]);
    if ( _(u3r_sung(key, u3h(kev))) ) {
      return u3a_gain(u3t(kev));
    }
  }
  return u3_none;
}

/* _ch_node_gut(): read in node, unifying key nouns.
*/
static u3_weak
_ch_node_gut(u3h_node* han_u, c3_w lef_w, c3_w rem_w, u3_noun key)
{
  c3_w bit_w, map_w;

  lef_w -= 5;
  bit_w = (rem_w >> lef_w);
  rem_w = (rem_w & ((1 << lef_w) - 1));
  map_w = han_u->map_w;

  if ( !(map_w & (1 << bit_w)) ) {
    return u3_none;
  }
  else {
    c3_w inx_w = _ch_popcount(map_w & ((1 << bit_w) - 1));
    c3_w sot_w = han_u->sot_w[inx_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      if ( _(u3r_sung(key, u3h(kev))) ) {
        return u3a_gain(u3t(kev));
      }
      else {
        return u3_none;
      }
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        return _ch_buck_gut(hav_v, key);
      }
      else return _ch_node_gut(hav_v, lef_w, rem_w, key);
    }
  }
}

/* u3h_gut(): read from hashtable, unifying key nouns.
**
** `key` is RETAINED.
*/
u3_weak
u3h_gut(u3p(u3h_root) har_p, u3_noun key)
{
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w mug_w        = u3r_mug(key);
  c3_w inx_w        = (mug_w >> 25);
  c3_w rem_w        = (mug_w & ((1 << 25) - 1));
  c3_w sot_w        = har_u->sot_w[inx_w];

  if ( _(u3h_slot_is_null(sot_w)) ) {
    return u3_none;
  }
  else if ( _(u3h_slot_is_noun(sot_w)) ) {
    u3_noun kev = u3h_slot_to_noun(sot_w);

    if ( _(u3r_sung(key, u3h(kev))) ) {
      har_u->sot_w[inx_w] = u3h_noun_be_warm(sot_w);
      return u3a_gain(u3t(kev));
    }
    else {
      return u3_none;
    }
  }
  else {
    u3h_node* han_u = u3h_slot_to_node(sot_w);

    return _ch_node_gut(han_u, 25, rem_w, key);
  }
}

/* _ch_free_buck(): free bucket
*/
static void
_ch_free_buck(u3h_buck* hab_u)
{
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    u3a_lose(u3h_slot_to_noun(hab_u->sot_w[i_w]));
  }
  u3a_wfree(hab_u);
}

/* _ch_free_node(): free node.
*/
static void
_ch_free_node(u3h_node* han_u, c3_w lef_w)
{
  c3_w len_w = _ch_popcount(han_u->map_w);
  c3_w i_w;

  lef_w -= 5;

  for ( i_w = 0; i_w < len_w; i_w++ ) {
    c3_w sot_w = han_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      u3a_lose(kev);
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        _ch_free_buck(hav_v);
      } else {
        _ch_free_node(hav_v, lef_w);
      }
    }
  }
  u3a_wfree(han_u);
}

/* u3h_free(): free hashtable.
*/
void
u3h_free(u3p(u3h_root) har_p)
{
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w        i_w;

  for ( i_w = 0; i_w < 64; i_w++ ) {
    c3_w sot_w = har_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      u3a_lose(kev);
    }
    else if ( _(u3h_slot_is_node(sot_w)) ) {
      u3h_node* han_u = u3h_slot_to_node(sot_w);

      _ch_free_node(han_u, 25);
    }
  }
  u3a_wfree(har_u);
}

/* _ch_walk_buck(): walk bucket for gc.
*/
static void
_ch_walk_buck(u3h_buck* hab_u, void (*fun_f)(u3_noun))
{
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    fun_f(u3h_slot_to_noun(hab_u->sot_w[i_w]));
  }
}

/* _ch_walk_node(): walk node for gc.
*/
static void
_ch_walk_node(u3h_node* han_u, c3_w lef_w, void (*fun_f)(u3_noun))
{
  c3_w len_w = _ch_popcount(han_u->map_w);
  c3_w i_w;

  lef_w -= 5;

  for ( i_w = 0; i_w < len_w; i_w++ ) {
    c3_w sot_w = han_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      fun_f(kev);
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        _ch_walk_buck(hav_v, fun_f);
      } else {
        _ch_walk_node(hav_v, lef_w, fun_f);
      }
    }
  }
}

/* u3h_walk(): walk hashtable for gc.
*/
void
u3h_walk(u3p(u3h_root) har_p, void (*fun_f)(u3_noun))
{
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w        i_w;

  for ( i_w = 0; i_w < 64; i_w++ ) {
    c3_w sot_w = har_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      fun_f(kev);
    }
    else if ( _(u3h_slot_is_node(sot_w)) ) {
      u3h_node* han_u = u3h_slot_to_node(sot_w);

      _ch_walk_node(han_u, 25, fun_f);
    }
  }
}

/* _ch_node_sane(): check node integrity.
*/
void
_ch_node_sane(u3h_node* han_u, c3_w lef_w)
{
  c3_w len_w = _ch_popcount(han_u->map_w);
  u3h_slot sot_w;

  lef_w -= 5;

  c3_assert(len_w > 0);
  c3_assert(1 == (u3a_botox(han_u))->use_w);

  if ( 1 == len_w ) {
    sot_w = han_u->sot_w[0];
    c3_assert(_(u3h_slot_is_node(sot_w)));
    _ch_some_sane(u3h_slot_to_node(sot_w), lef_w);
  }
  else {
    c3_w i_w;

    for ( i_w = 0; i_w < len_w; i_w++ ) {
      sot_w = han_u->sot_w[i_w];
      c3_assert(c3n == u3h_slot_is_null(sot_w));

      if ( _(u3h_slot_is_noun(sot_w)) ) {
        continue;
      }
      else if ( _(u3h_slot_is_node(sot_w)) ) {
        _ch_some_sane(u3h_slot_to_node(sot_w), lef_w);
      }
      else {
        c3_assert(0);  //  unknown contents
      }
    }
  }
}

/* _ch_buck_sane(): check bucket integrity.
*/
void
_ch_buck_sane(u3h_buck* hab_u, c3_w lef_w)
{
  //  XX fill in.
}

void
_ch_some_sane(void* han_v, c3_w lef_w)
{
  if ( 0 == lef_w ) {
    _ch_buck_sane((u3h_buck*)han_v, lef_w);
  }
  else _ch_node_sane((u3h_node*)han_v, lef_w);
}

/* u3h_sane(): check hashtable integrity.
*/
void
u3h_sane(u3p(u3h_root) har_p)
{
  c3_w i_w;
  u3h_root* har_u = u3to(u3h_root, har_p);
  u3h_slot sot_w;

  for ( i_w = 0; i_w < 64; i_w++ ) {
    sot_w = har_u->sot_w[i_w];
    if ( _(u3h_slot_is_null(sot_w)) ) {
      continue;
    }
    else if ( _(u3h_slot_is_noun(sot_w)) ) {
      continue;
    }
    else if ( _(u3h_slot_is_node(sot_w)) ) {
      u3h_node* han_u = u3h_slot_to_node(sot_w);

      _ch_node_sane(han_u, 25);
    }
    else {
      c3_assert(0);  //  unknown contents
    }
  }
}

/* _ch_mark_buck(): mark bucket for gc.
*/
c3_w
_ch_mark_buck(u3h_buck* hab_u)
{
  c3_w tot_w = 0;
  c3_w i_w;

  for ( i_w = 0; i_w < hab_u->len_w; i_w++ ) {
    tot_w += u3a_mark_noun(u3h_slot_to_noun(hab_u->sot_w[i_w]));
  }
  tot_w += u3a_mark_ptr(hab_u);

  return tot_w;
}

/* _ch_mark_node(): mark node for gc.
*/
c3_w
_ch_mark_node(u3h_node* han_u, c3_w lef_w)
{
  c3_w tot_w = 0;
  c3_w len_w = _ch_popcount(han_u->map_w);
  c3_w i_w;

  lef_w -= 5;

  for ( i_w = 0; i_w < len_w; i_w++ ) {
    c3_w sot_w = han_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      tot_w += u3a_mark_noun(kev);
    }
    else {
      void* hav_v = u3h_slot_to_node(sot_w);

      if ( 0 == lef_w ) {
        tot_w += _ch_mark_buck(hav_v);
      } else {
        tot_w += _ch_mark_node(hav_v, lef_w);
      }
    }
  }

  tot_w += u3a_mark_ptr(han_u);

  return tot_w;
}

/* u3h_mark(): mark hashtable for gc.
*/
c3_w
u3h_mark(u3p(u3h_root) har_p)
{
  c3_w tot_w = 0;
  u3h_root* har_u = u3to(u3h_root, har_p);
  c3_w        i_w;

  for ( i_w = 0; i_w < 64; i_w++ ) {
    c3_w sot_w = har_u->sot_w[i_w];

    if ( _(u3h_slot_is_noun(sot_w)) ) {
      u3_noun kev = u3h_slot_to_noun(sot_w);

      tot_w += u3a_mark_noun(kev);
    }
    else if ( _(u3h_slot_is_node(sot_w)) ) {
      u3h_node* han_u = u3h_slot_to_node(sot_w);

      tot_w += _ch_mark_node(han_u, 25);
    }
  }

  tot_w += u3a_mark_ptr(har_u);

  return tot_w;
}
