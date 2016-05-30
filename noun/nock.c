/* g/n.c
**
*/
#include "all.h"
#include <stdarg.h>
#include <jit/jit.h>
#include <jit/jit-dump.h>

static struct {
  jit_context_t cex;
  c3_w          hop;   /* prev allocated size of hot  */
  c3_w          hos;   /* allocated size of hot       */
  u3_chit       top;
  u3_funk*      hot;
} u3n_Jit;

static u3_noun _n_nock_on(u3_noun bus, u3_noun fol);
static jit_value_t _nj_nock(jit_function_t f, jit_value_t bus, u3_noun fol);

      /* u3_term_io_hija(): hijack console for cooked print.
      */
        FILE*
        u3_term_io_hija(void);

      /* u3_term_io_loja(): release console from cooked print.
      */
        void
        u3_term_io_loja(int x);

      /* uL, uH: wrap hijack/lojack around fprintf.
      **
      **  uL(fprintf(uH, ...));
      */
#       define uH    u3_term_io_hija()
#       define uL(x) u3_term_io_loja(x)


/* _n_hint(): process hint.
*/
static u3_noun
_n_hint(u3_noun zep, 
        u3_noun hod,
        u3_noun bus,
        u3_noun nex)
{
  switch ( zep ) {
    default: {
      // u3m_p("weird zep", zep);
      u3a_lose(zep);
      u3a_lose(hod);

      return _n_nock_on(bus, nex);
    }

    case c3__hunk:
    case c3__lose:
    case c3__mean:
    case c3__spot: {
      u3_noun tac = u3nc(zep, hod);
      u3_noun pro;

      u3t_push(tac);
#if 0
      {
        static int low_i;

        if ( !low_i ) {
          low_i = 1;
          if ( 0 == (u3R->pro.nox_d % 65536ULL) ) {
            if ( c3__spot == zep ) {
              uL(fprintf(uH, "spot %d/%d : %d/%d\r\n",
                             u3h(u3h(u3t(hod))),
                             u3t(u3h(u3t(hod))),
                             u3h(u3t(u3t(hod))),
                             u3t(u3t(u3t(hod)))));
            }
          }
          low_i = 0;
        }
      }
#endif
      pro = _n_nock_on(bus, nex);
      u3t_drop();

      return pro;
    }

    case c3__live: {
      if ( c3y == u3ud(hod) ) {
        u3t_off(noc_o);
        u3t_heck(hod);
        u3t_on(noc_o);
      } else {
        u3z(hod);
      }
      return _n_nock_on(bus, nex);
    }

    case c3__slog: {
      if ( !(u3C.wag_w & u3o_quiet) ) {
        u3t_off(noc_o);
        u3t_slog(hod);
        u3t_on(noc_o);
      }
      return _n_nock_on(bus, nex);
    }

    case c3__germ: {
      u3_noun pro = _n_nock_on(bus, nex);

      if ( c3y == u3r_sing(pro, hod) ) {
        u3z(pro); return hod;
      } else {
        u3z(hod); return pro;
      }
    }

    case c3__fast: {
      u3_noun pro = _n_nock_on(bus, nex);

      u3t_off(noc_o);
      u3j_mine(hod, u3k(pro));
      u3t_on(noc_o);

      return pro;
    }

    case c3__memo: {
      u3z(hod);
#if 0
      return _n_nock_on(bus, nex);
#else
      {
        u3_noun pro = u3z_find_2(c3__nock, bus, nex);

        if ( pro != u3_none ) {
          u3z(bus); u3z(nex);
          return pro;
        }
        pro = _n_nock_on(u3k(bus), u3k(nex));

        if ( &(u3H->rod_u) != u3R ) {
          u3z_save_2(c3__nock, bus, nex, pro);
        }

        u3z(bus); u3z(nex);

        return pro;
      }
#endif
    }

    case c3__sole: {
      u3z(hod);
      {
        u3_noun pro = _n_nock_on(bus, nex);

        // return u3z_uniq(pro);
        return pro;
      }
    }
  }
}

/* _n_mush_in(): see _n_mush().
*/
static u3_noun
_n_mush_in(u3_noun val)
{
  if ( c3n == u3du(val) ) {
    return u3_nul;
  }
  else {
    u3_noun h_val = u3h(val);
    u3_noun ite;

    if ( c3n == u3ud(h_val) ) {
      ite = u3nc(c3__leaf, u3_nul);
    } else {
      ite = u3nc(c3__leaf, u3qe_trip(h_val));
    }
    return u3nc(ite, _n_mush_in(u3t(val)));
  }
}

/* _n_mush(): tank from failed path request.
*/
static u3_noun 
_n_mush(u3_noun val)
{
  u3_noun pro;

  pro = u3nt(c3__rose,
             u3nt(u3nc('/', u3_nul), u3nc('/', u3_nul), u3_nul),
             _n_mush_in(val));
  u3z(val);
  return pro;
}

/* _n_nock_on(): produce .*(bus fol).  Do not virtualize.
*/
static u3_noun
_n_nock_on(u3_noun bus, u3_noun fol)
{
  u3_noun hib, gal;

  while ( 1 ) {
    hib = u3h(fol);
    gal = u3t(fol);

    u3R->pro.nox_d += 1;

    if ( c3y == u3r_du(hib) ) {
      u3_noun poz, riv;

      poz = _n_nock_on(u3k(bus), u3k(hib));
      riv = _n_nock_on(bus, u3k(gal));

      u3a_lose(fol);
      return u3i_cell(poz, riv);
    }
    else switch ( hib ) {
      default: return u3m_bail(c3__exit);

      case 0: {
        if ( c3n == u3r_ud(gal) ) {
          return u3m_bail(c3__exit);
        }
        else {
          u3_noun pro = u3k(u3at(gal, bus));

          u3a_lose(bus); u3a_lose(fol);
          return pro;
        }
      }
      c3_assert(!"not reached");

      case 1: {
        u3_noun pro = u3k(gal);

        u3a_lose(bus); u3a_lose(fol);
        return pro;
      }
      c3_assert(!"not reached");

      case 2: {
        u3_noun nex = _n_nock_on(u3k(bus), u3k(u3t(gal)));
        u3_noun seb = _n_nock_on(bus, u3k(u3h(gal)));

        u3a_lose(fol);
        bus = seb;
        fol = nex;
        continue;
      }
      c3_assert(!"not reached");

      case 3: {
        u3_noun gof, pro;

        gof = _n_nock_on(bus, u3k(gal));
        pro = u3r_du(gof);

        u3a_lose(gof); u3a_lose(fol);
        return pro;
      }
      c3_assert(!"not reached");

      case 4: {
        u3_noun gof, pro;

        gof = _n_nock_on(bus, u3k(gal));
        pro = u3i_vint(gof);

        u3a_lose(fol);
        return pro;
      }
      c3_assert(!"not reached");

      case 5: {
        u3_noun wim = _n_nock_on(bus, u3k(gal));
        u3_noun pro = u3r_sing(u3h(wim), u3t(wim));

        u3a_lose(wim); u3a_lose(fol);
        return pro;
      }
      c3_assert(!"not reached");

      case 6: {
        u3_noun b_gal, c_gal, d_gal;

        u3x_trel(gal, &b_gal, &c_gal, &d_gal);
        {
          u3_noun tys = _n_nock_on(u3k(bus), u3k(b_gal));
          u3_noun nex;

          if ( 0 == tys ) {
            nex = u3k(c_gal);
          } else if ( 1 == tys ) {
            nex = u3k(d_gal);
          } else return u3m_bail(c3__exit);

          u3a_lose(fol);
          fol = nex;
          continue;
        }
      }
      c3_assert(!"not reached");

      case 7: {
        u3_noun b_gal, c_gal;

        u3x_cell(gal, &b_gal, &c_gal);
        {
          u3_noun bod = _n_nock_on(bus, u3k(b_gal));
          u3_noun nex = u3k(c_gal);

          u3a_lose(fol);
          bus = bod;
          fol = nex;
          continue;
        }
      }
      c3_assert(!"not reached");

      case 8: {
        u3_noun b_gal, c_gal;

        u3x_cell(gal, &b_gal, &c_gal);
        {
          u3_noun heb = _n_nock_on(u3k(bus), u3k(b_gal));
          u3_noun bod = u3nc(heb, bus);
          u3_noun nex = u3k(c_gal);

          u3a_lose(fol);
          bus = bod;
          fol = nex;
          continue;
        }
      }
      c3_assert(!"not reached");

      case 9: {
        u3_noun b_gal, c_gal;

        u3x_cell(gal, &b_gal, &c_gal);
        {
          u3_noun seb = _n_nock_on(bus, u3k(c_gal));
          u3_noun pro;
         
          u3t_off(noc_o);
          pro = u3j_kick(seb, b_gal);
          u3t_on(noc_o);

          if ( u3_none != pro ) {
            u3a_lose(fol);
            return pro;
          }
          else {
            if ( c3n == u3r_ud(b_gal) ) {
              return u3m_bail(c3__exit);
            }
            else {
              u3_noun nex = u3k(u3at(b_gal, seb));

              u3a_lose(fol);
              bus = seb;
              fol = nex;
              continue;
            }
          }
        }
      }
      c3_assert(!"not reached");

      case 10: {
        u3_noun p_gal, q_gal;

        u3x_cell(gal, &p_gal, &q_gal);
        {
          u3_noun zep, hod, nex;

          if ( c3y == u3r_du(p_gal) ) {
            u3_noun b_gal = u3h(p_gal);
            u3_noun c_gal = u3t(p_gal);
            u3_noun d_gal = q_gal;

            zep = u3k(b_gal);
            hod = _n_nock_on(u3k(bus), u3k(c_gal));
            nex = u3k(d_gal);
          }
          else {
            u3_noun b_gal = p_gal;
            u3_noun c_gal = q_gal;

            zep = u3k(b_gal);
            hod = u3_nul;
            nex = u3k(c_gal);
          }

          u3a_lose(fol);
          return _n_hint(zep, hod, bus, nex);
        }
      }

      case 11: {
        u3_noun ref = _n_nock_on(u3k(bus), u3k(u3h(gal)));
        u3_noun gof = _n_nock_on(bus, u3k(u3t(gal)));
        u3_noun val;

        u3t_off(noc_o);
        val = u3m_soft_esc(ref, u3k(gof));
        u3t_on(noc_o);

        if ( !_(u3du(val)) ) {
          u3m_bail(u3nt(1, gof, 0));
        } 
        if ( !_(u3du(u3t(val))) ) {
          //
          //  replace with proper error stack push
          //
          u3t_push(u3nc(c3__hunk, _n_mush(gof)));
          return u3m_bail(c3__exit);
        }
        else {
          u3_noun pro;

          u3z(gof);
          u3z(fol);
          pro = u3k(u3t(u3t(val)));
          u3z(val);

          return pro;
        }
      }  
      c3_assert(!"not reached");
    }
  }
}

/* u3n_nock_on(): produce .*(bus fol).  Do not virtualize.
*/
u3_noun
u3n_nock_on(u3_noun bus, u3_noun fol)
{
  u3_noun pro;

  u3t_on(noc_o);
  pro = _n_nock_on(bus, fol);
  u3t_off(noc_o);

  return pro;
}

/* u3n_kick_on(): fire `gat` without changing the sample.
*/
u3_noun
u3n_kick_on(u3_noun gat)
{
  return u3j_kink(gat, 2);
}

c3_w exc_w;

/* u3n_slam_on(): produce (gat sam).
*/
u3_noun
u3n_slam_on(u3_noun gat, u3_noun sam)
{
  u3_noun cor = u3nc(u3k(u3h(gat)), u3nc(sam, u3k(u3t(u3t(gat)))));

#if 0
  if ( &u3H->rod_u == u3R ) {
    if ( exc_w == 1 ) {
      c3_assert(0);
    } 
    exc_w++;
  }
#endif
  u3z(gat);
  return u3n_kick_on(cor);
}

/* u3n_nock_et(): produce .*(bus fol), as ++toon, in namespace.
*/
u3_noun
u3n_nock_et(u3_noun gul, u3_noun bus, u3_noun fol)
{
  return u3m_soft_run(gul, u3n_nock_on, bus, fol);
}

/* u3n_slam_et(): produce (gat sam), as ++toon, in namespace.
*/
u3_noun
u3n_slam_et(u3_noun gul, u3_noun gat, u3_noun sam)
{
  return u3m_soft_run(gul, u3n_slam_on, gat, sam);
}

/* u3n_nock_an(): as slam_in(), but with empty fly.
*/
u3_noun
u3n_nock_an(u3_noun bus, u3_noun fol)
{
  u3_noun gul = u3nt(u3nt(1, 0, 0), 0, 0);  //  |=(a/{* *} ~)

  return u3n_nock_et(gul, bus, fol);
}

static jit_type_t
_nj_sig(c3_o ret_o, c3_w arg_w)
{
  jit_type_t *arg = alloca(arg_w*sizeof(jit_type_t));
  c3_w       i_w;

  for ( i_w = 0; i_w < arg_w; i_w++ ) {
    arg[i_w] = jit_type_uint;
  }

  return jit_type_create_signature(
    jit_abi_cdecl,
    (_(ret_o) ? jit_type_uint : jit_type_void),
    arg, arg_w, 1);
}

static jit_value_t
_nj_nat(jit_function_t f, const char *name, 
        void *fun_f, c3_o ret_o, c3_w arg_w, ...)
{
  jit_value_t *arg = alloca(arg_w*sizeof(jit_value_t));
  c3_w i_w;
  va_list vap;

  va_start(vap, arg_w);

  for ( i_w = 0; i_w < arg_w; i_w++ ) {
    arg[i_w] = va_arg(vap, jit_value_t);
  }
  
  va_end(vap);

  return jit_insn_call_native(f, name,
    fun_f, _nj_sig(ret_o, arg_w), (void*) arg, arg_w, JIT_CALL_NOTHROW);
}

static void
_nj_bail(jit_function_t f, jit_value_t wit)
{
  jit_insn_call_native(
    f, "u3m_bail", u3m_bail, _nj_sig(c3n, 1), &wit, 1, JIT_CALL_NORETURN);
}

static jit_value_t
_nj_call_nock(jit_function_t f, jit_value_t bus, jit_value_t fol)
{
  // NOTHROW is not appropriate, since we'll be jitting and may throw.
  jit_value_t jit = jit_insn_call_native(
    f, "u3n_compile", u3n_compile, _nj_sig(c3y, 1), &fol, 1, 0);

  return _nj_nat(f, "u3n_nock_chit", u3n_nock_chit, c3y, 2, bus, jit);
}

static jit_value_t
_nj_w(jit_function_t f, c3_w i)
{
  return jit_value_create_nint_constant(f, jit_type_uint, i);
}

static jit_value_t
_nj_p(jit_function_t f, void *p)
{
  return jit_value_create_nint_constant(f, jit_type_void_ptr, (jit_nint) p);
}

static jit_value_t
_nj_gain(jit_function_t f, jit_value_t a)
{
  return _nj_nat(f, "u3k", u3a_gain, c3y, 1, a);
}

static void
_nj_lose(jit_function_t f, jit_value_t a)
{
  _nj_nat(f, "u3z", u3a_lose, c3n, 1, a);
}

static jit_value_t
_nj_du(jit_function_t f, jit_value_t a)
{
  return jit_insn_ne(
      f, jit_insn_ushr(f, a, _nj_w(f, 30)), _nj_w(f, 3));
}

static jit_value_t
_nj_cell(jit_function_t f, jit_value_t a, jit_value_t b)
{
  return _nj_nat(f, "[]", u3i_cell, c3y, 2, a, b);
}

static jit_value_t
_nj_sing(jit_function_t f, jit_value_t a, jit_value_t b)
{
  return _nj_nat(f, "=", u3r_sing, c3y, 2, a, b);
}

static jit_value_t
_nj_f(jit_function_t f, jit_value_t a, jit_nint o)
{
  jit_value_t ptr = jit_insn_load_elem_address(f,
    _nj_p(f, u3_Loom),
    jit_insn_and(f, a, _nj_w(f, 0x3fffffff)),
    jit_type_uint);

  return jit_insn_load_relative(f, ptr, o, jit_type_uint);
}

static jit_value_t
_nj_h(jit_function_t f, jit_value_t a)
{
  return _nj_f(f, a, offsetof(u3a_cell, hed));
}

static jit_value_t
_nj_t(jit_function_t f, jit_value_t a)
{
  return _nj_f(f, a, offsetof(u3a_cell, tel));
}

static void
_nj_switch_trace(jit_function_t f, jit_nint off, c3_o on_o)
{
  jit_type_t sig = jit_type_create_signature(
      jit_abi_cdecl, jit_type_void, NULL, 0, 1);

  jit_label_t fin = jit_label_undefined;
  jit_value_t bas, val, yes, neg, bad;

  if ( u3C.wag_w & u3o_debug_cpu )
  {
    bas = _nj_p(f, &u3T);
    val = jit_insn_load_relative(f, bas, off, jit_type_ubyte);
    yes = jit_value_create_nint_constant(f, jit_type_ubyte, on_o);
    neg = jit_value_create_nint_constant(f, jit_type_ubyte, !on_o);
    bad = jit_insn_eq(f, yes, val);
    jit_insn_branch_if_not(f, bad, &fin);
    jit_insn_call_native(f, "abort", abort, sig, NULL, 0, JIT_CALL_NORETURN);
    jit_insn_label(f, &fin);
    jit_insn_store_relative(f, bas, off, neg);
  }
}

static void
_nj_switch_noc(jit_function_t f, c3_o on_o)
{
  _nj_switch_trace(f, offsetof(u3t_trace, noc_o), on_o);
}

/* RETAIN */
static jit_value_t
_nj_at(jit_function_t f, u3_noun a, jit_value_t b) {
  c3_assert(u3_none != a);

  c3_w*       buf_w;
  c3_w        len_w, dep_w, i_w, a_w;
  jit_label_t fin = jit_label_undefined,
              bal = jit_label_undefined;
  jit_value_t ret = jit_value_create(f, jit_type_uint);

  // FIXME: jitted code should assert b (its argument)

#ifdef U3_CPU_DEBUG
  _nj_switch_trace(f, offsetof(u3t_trace, far_o), c3y);
#endif

  if ( 0 != a && !_(u3a_is_cell(a)) )
  {
    if ( _(u3a_is_cat(a)) )
    {
      buf_w = &a;
      len_w = 1;
    }
    else
    {
      u3a_atom* tom_u = u3a_to_ptr(a);
      buf_w = tom_u->buf_w;
      len_w = tom_u->len_w;
    }

    jit_insn_store(f, ret, b);

    for ( i_w = 0; i_w < len_w; i_w++ )
    {
      a_w   = buf_w[len_w - (i_w + 1)];
      dep_w = (i_w == 0 ? u3x_dep(a_w) : 32);
      while ( dep_w )
      {
        jit_insn_branch_if(f, _nj_du(f, ret), &bal);
        jit_insn_store(f, ret,
          (1 & (a_w >> --dep_w))
          ? _nj_t(f, ret)
          : _nj_h(f, ret));
      }
    }
    jit_insn_branch(f, &fin);
    jit_insn_label(f, &bal);
  }
  jit_insn_store(f, ret, _nj_w(f, u3_none));
  jit_insn_label(f, &fin);

#ifdef U3_CPU_DEBUG
  _nj_switch_trace(f, offsetof(u3t_trace, far_o), c3n);
#endif

  return ret;
}

static jit_value_t
_nj_hint(jit_function_t f,
  u3_noun zep, jit_value_t hod, jit_value_t bus, u3_noun nex)
{
  switch ( zep ) {
    default: {
      _nj_lose(f, hod);
      return _nj_nock(f, bus, nex);
    }

    case c3__hunk:
    case c3__lose:
    case c3__mean:
    case c3__spot: {
      jit_value_t pro, tac;

      tac = _nj_cell(f,  _nj_w(f, zep), hod);

      _nj_nat(f, "u3t_push", u3t_push, c3n, 1, tac);
      pro = _nj_nock(f, bus, nex);
      _nj_nat(f, "u3t_drop", u3t_drop, c3n, 0);

      return pro;
    }

    case c3__live: {
      jit_label_t one, two;

      jit_insn_branch_if_not(f, _nj_du(f, hod), &one);

      _nj_switch_noc(f, c3n);
      _nj_nat(f, "u3t_heck", u3t_heck, c3n, 1, hod);
      _nj_switch_noc(f, c3y);
      jit_insn_branch(f, &two);

      jit_insn_label(f, &one);
      _nj_lose(f, hod);

      jit_insn_label(f, &two);
      return _nj_nock(f, bus, nex);
    }

    case c3__slog: {
      if ( !(u3C.wag_w & u3o_quiet) ) {
        _nj_switch_noc(f, c3n);
        _nj_nat(f, "u3t_slog", u3t_slog, c3n, 1, hod);
        _nj_switch_noc(f, c3y);
      }
      return _nj_nock(f, bus, nex);
    }

    case c3__germ: {
      jit_label_t one, fin;
      jit_value_t pro;
      
      pro = _nj_nock(f, bus, nex);

      jit_insn_branch_if(f, _nj_sing(f, pro, hod), &one);
      _nj_lose(f, pro);
      jit_insn_store(f, pro, hod);
      jit_insn_branch(f, &fin);

      jit_insn_label(f, &one);
      _nj_lose(f, hod);

      jit_insn_label(f, &fin);

      return pro;
    }

    case c3__fast: {
      jit_value_t pro; 
      
      pro = _nj_nock(f, bus, nex);

      _nj_switch_noc(f, c3n);
      _nj_nat(f, "u3j_mine", u3j_mine, c3n, 2, hod, _nj_gain(f, pro));
      _nj_switch_noc(f, c3y);

      return pro;
    }

    case c3__memo: {
      jit_label_t fin;
      jit_value_t pro, jnx, out, roa, rod, mot;

      _nj_lose(f, hod);

      mot = _nj_w(f, c3__nock);
      jnx = _nj_w(f, u3k(nex));
      pro = _nj_nat(f, "u3z_find_2", u3z_find_2, c3y, 3, mot, bus, jnx);

      jit_insn_branch_if(f, jit_insn_ne(f, pro, _nj_w(f, u3_none)), &fin);

      jit_insn_store(f, pro, _nj_nock(f, _nj_gain(f, bus), nex));
      out = _nj_p(f, &(u3H->rod_u));
      roa = _nj_p(f, &u3R);
      rod = jit_insn_load_relative(f, roa, 0, jit_type_void_ptr);
      jit_insn_branch_if(f, jit_insn_eq(f, out, rod), &fin);

      _nj_nat(f, "u3z_save_2",
        u3z_save_2, c3n, 4, mot, bus, jnx, pro);

      jit_insn_label(f, &fin);
      _nj_lose(f, bus);

      return pro;
    }

    case c3__sole: {
      _nj_lose(f, hod);
      return _nj_nock(f, bus, nex);
    }
  }
}

/* fol is RETAINED by the caller.
 * The compiled function has transfer semantics exactly as _n_nock_on.
 */
static jit_value_t
_nj_nock(jit_function_t f, jit_value_t bus, u3_noun fol)
{
  static c3_w noo_w = offsetof(u3a_road, pro.nox_d);
  u3_noun     hib, gal;
  jit_value_t roa   = _nj_p(f, &u3R), rod;

  // u3R->pro.nox_d += 1;
  rod = jit_insn_load_relative(f, roa, 0, jit_type_void_ptr);
  jit_insn_store_relative(f, rod, noo_w,
    jit_insn_add(f, _nj_w(f, 1),
      jit_insn_load_relative(f, rod, noo_w, jit_type_ulong)));

  hib = u3h(fol);
  gal = u3t(fol);

  if ( c3y == u3r_du(hib) ) {
    jit_value_t poz, riv;

    poz = _nj_nock(f, _nj_gain(f, bus), hib);
    riv = _nj_nock(f, bus, gal);

    return _nj_cell(f, poz, riv); 
  }
  switch ( hib ) {
    default: u3m_bail(c3__exit);

    case 0: {
      if ( c3n == u3r_ud(gal) ) {
        u3m_bail(c3__exit);
      }
      else {
        jit_value_t ret = _nj_gain(f, _nj_at(f, gal, bus));
        _nj_lose(f, bus);
        return ret;
      }
    }

    case 1: {
      jit_value_t qot = _nj_gain(f, _nj_w(f, u3k(gal)));
      _nj_lose(f, bus);
      return qot;
    }

    case 2: {
      jit_value_t poz, riv;
      poz = _nj_nock(f, _nj_gain(f, bus), u3h(gal));
      riv = _nj_nock(f, bus, u3t(gal));

      return _nj_call_nock(f, poz, riv);
    }

    case 3: {
      jit_value_t gof, pro;

      gof = _nj_nock(f, bus, gal);
      pro = jit_insn_to_bool(f, _nj_du(f, gof));
      _nj_lose(f, gof);

      return pro;
    }

    case 4: {
      jit_value_t gof, pro;

      gof = _nj_nock(f, bus, gal);
      pro = _nj_nat(f, "+", u3i_vint, c3y, 1, gof);

      return pro;
    }

    case 5: {
      jit_value_t wim, pro;

      wim = _nj_nock(f, bus, gal);
      pro = _nj_sing(f, _nj_h(f, wim), _nj_t(f, wim));
      _nj_lose(f, wim);

      return pro;
    }

    case 6: {
      u3_noun b_gal, c_gal, d_gal;

      u3x_trel(gal, &b_gal, &c_gal, &d_gal);
      {
        jit_label_t one = jit_label_undefined,
                    fin = jit_label_undefined,
                    bal = jit_label_undefined;
        jit_value_t tys = _nj_nock(f, _nj_gain(f, bus), b_gal),
                    nex = jit_value_create(f, jit_type_uint),
                    yes = _nj_w(f, c3y),
                    non = _nj_w(f, c3n);

        jit_insn_branch_if(f, jit_insn_ne(f, tys, yes), &one);
        jit_insn_store(f, nex, _nj_nock(f, bus, c_gal));
        jit_insn_branch(f, &fin);

        jit_insn_label(f, &one);
        jit_insn_branch_if(f, jit_insn_ne(f, tys, non), &bal);
        jit_insn_store(f, nex, _nj_nock(f, bus, d_gal));
        jit_insn_branch(f, &fin);

        jit_insn_label(f, &bal);
        _nj_bail(f, _nj_w(f, c3__exit));

        jit_insn_label(f, &fin);
        return nex;
      }
    }

    case 7: {
      u3_noun b_gal, c_gal;

      u3x_cell(gal, &b_gal, &c_gal);
      {
        return _nj_nock(f, _nj_nock(f, bus, b_gal), c_gal);
      }
    }

    case 8: {
      u3_noun b_gal, c_gal;

      u3x_cell(gal, &b_gal, &c_gal);
      {
        jit_value_t heb = _nj_nock(f, _nj_gain(f, bus), b_gal);
        return _nj_nock(f, _nj_cell(f, heb, bus), c_gal);
      }
    }

    case 9: {
      u3_noun b_gal, c_gal;

      u3x_cell(gal, &b_gal, &c_gal);
      {
        jit_label_t fin = jit_label_undefined;
        jit_value_t axe, pro, seb, nex;

        if ( c3n == u3r_ud(b_gal) ) {
          u3m_bail(c3__exit);
        }

        seb = _nj_nock(f, bus, c_gal);
        axe = _nj_w(f, u3k(b_gal));

        _nj_switch_noc(f, c3n);
        pro = _nj_nat(f, "u3j_kick", u3j_kick, c3y, 2, seb, axe);
        _nj_switch_noc(f, c3y);

        jit_insn_branch_if(f, jit_insn_ne(f, pro, _nj_w(f, u3_none)), &fin);

        nex = _nj_gain(f, _nj_at(f, b_gal, seb));
        jit_insn_store(f, pro, _nj_call_nock(f, seb, nex));

        jit_insn_label(f, &fin);
        return pro;
      }
    }

    case 10: {
      u3_noun p_gal, q_gal;

      u3x_cell(gal, &p_gal, &q_gal);
      {
        u3_noun     zep, nex;
        jit_value_t hod;

        if ( c3y == u3r_du(p_gal) ) {
          zep = u3h(p_gal);
          hod = _nj_nock(f, _nj_gain(f, bus), u3t(p_gal));
          nex = q_gal;
        }
        else {
          zep = p_gal;
          hod = _nj_w(f, u3_nul);
          nex = q_gal;
        }
        return _nj_hint(f, zep, hod, bus, nex);
      }
    }

    case 11: {
      jit_label_t one, two, fin;
      jit_value_t ref, gof, val, oop, pro; 
      
      ref = _nj_nock(f, _nj_gain(f, bus), u3h(gal)),
      gof = _nj_nock(f, bus, u3t(gal)),
      pro = jit_value_create(f, jit_type_uint);

      _nj_switch_noc(f, c3n);
      val = _nj_nat(f, "u3m_soft_esc",
          u3m_soft_esc, c3y, 2, ref, _nj_gain(f, gof));
      _nj_switch_noc(f, c3y);

      jit_insn_branch_if(f, _nj_du(f, val), &one);
      jit_insn_branch_if(f, _nj_du(f, _nj_t(f, val)), &two);

      _nj_lose(f, gof);
      jit_insn_store(f, pro, _nj_gain(f, _nj_t(f, _nj_t(f, val))));
      _nj_lose(f, val);
      jit_insn_branch(f, &fin);

      jit_insn_label(f, &one);
      oop = _nj_cell(f, _nj_w(f, 1), _nj_cell(f, gof, _nj_w(f, 0)));
      _nj_bail(f, oop);

      jit_insn_label(f, &two);
      oop = _nj_cell(f,
        _nj_w(f, c3__hunk),
        _nj_nat(f, "_n_mush", _n_mush, c3y, 1, gof));
      _nj_nat(f, "u3t_push", u3t_push, c3n, 1, oop);
      _nj_bail(f, _nj_w(f, c3__exit));

      jit_insn_label(f, &fin);
      return pro;
    }  
  }
}

void
u3n_boot_jit()
{
  u3n_Jit.cex   = jit_context_create();
  u3n_Jit.top   = 0;
  u3n_Jit.hos   = 987; /* fib(16) */
  u3n_Jit.hop   = 610; /* fib(15) */
  u3n_Jit.hot   = malloc(987 * sizeof(u3_funk));
  u3R->jis.nex  = 0;
}

static u3_funk
_n_compile(u3_noun fol)
{
  jit_function_t f;
  jit_context_t  c;
  c = u3n_Jit.cex;
  jit_context_build_start(c);
  f = jit_function_create(c, _nj_sig(c3y, 1));
  jit_insn_return(f, _nj_nock(f, jit_value_get_param(f, 0), fol));
  jit_context_build_end(c);
  jit_function_compile(f);
  return jit_function_to_closure(f);
}

static void
_n_grow_hot(c3_w top)
{
  c3_w hos = u3n_Jit.hos;
  c3_w hop = u3n_Jit.hop;

  while ( top >= hos ) {
    c3_w siz = hop + hos;
    hop = hos;
    hos = siz;
  }

  u3n_Jit.hos = hos;
  u3n_Jit.hop = hop;
  u3n_Jit.top = top;
  u3n_Jit.hot = realloc(u3n_Jit.hot, hos * sizeof(u3_funk));
}

u3_chit
u3n_compile(u3_noun fol)
{
  u3a_road* rod_u;
  u3_chit   jit;

  for ( rod_u = u3R; rod_u; rod_u = u3tn(u3_road, rod_u->par_p) ) {
    jit = u3h_get(rod_u->jis.fit, fol);
    if (jit != u3_none) {
      return jit;
    }
  }

  jit = u3R->jis.nex++;
  u3h_put(u3R->jis.fit, fol, jit);
  u3h_put(u3R->jis.tif, jit, fol);

  if (u3R == &(u3H->rod_u)) {
    _n_grow_hot(jit);
    u3n_Jit.hot[jit] = _n_compile(fol);
  }

  return jit;
}

u3_noun
u3n_nock_chit(u3_noun bus, u3_chit jit)
{
  u3a_road* rod_u;
  u3_noun   fol;

  if (jit <= u3n_Jit.top) {
    return u3n_Jit.hot[jit](bus);
  }

  for ( rod_u = u3R; rod_u; rod_u = u3tn(u3_road, rod_u->par_p) ) {
    fol = u3h_get(rod_u->jis.tif, jit);
    if (fol != u3_none) {
      return _n_nock_on(bus, fol);
    }
  }

  u3m_bail(c3__exit);
}

static void
_n_fit_kep(u3_noun kev)
{
  u3_noun key = u3a_take(u3h(kev));
  u3_noun val = u3a_take(u3t(kev));

  u3h_put(u3R->jis.fit, key, val);
}

static void
_n_tif_kep(u3_noun kev)
{
  u3_noun key = u3a_take(u3h(kev));
  u3_noun val = u3a_take(u3t(kev));

  u3h_put(u3R->jis.tif, key, val);
}

static void
_n_tif_ins(u3_noun kev)
{
  u3_noun key = u3a_take(u3h(kev));
  u3_noun val = u3a_take(u3t(kev));

  u3n_Jit.hot[key] = _n_compile(val);
  u3z(val);
}

void
u3n_heat(u3p(u3h_root) fit, u3p(u3h_root) tif, u3_chit nex)
{
  u3R->jis.nex = nex;

  u3h_walk(fit, _n_fit_kep);

  if ( u3R == &(u3H->rod_u) ) {
    _n_grow_hot(nex - 1);
    u3h_walk(tif, _n_tif_ins);
  }
  else {
    u3h_walk(tif, _n_tif_kep);
  }
}
