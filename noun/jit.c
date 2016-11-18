#include "all.h"
#include <jit/jit.h>

static jit_context_t cex;

static jit_value_t _nock(jit_function_t, jit_value_t, u3_noun);
//static u3_noun _to_nock(u3_noun nec, u3_noun fol);

static jit_type_t
_sig(c3_o ret_o, c3_w arg_w)
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
_nat(jit_function_t f, const char *name,
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
    fun_f, _sig(ret_o, arg_w), (void*) arg, arg_w, JIT_CALL_NOTHROW);
}

static jit_value_t
_w(jit_function_t f, c3_w i)
{
  return jit_value_create_nint_constant(f, jit_type_uint, i);
}

static jit_value_t
_gain(jit_function_t f, jit_value_t a)
{
  return _nat(f, "u3k", u3a_gain, c3y, 1, a);
}

static void
_lose(jit_function_t f, jit_value_t a)
{
  _nat(f, "u3z", u3a_lose, c3n, 1, a);
}

static jit_value_t
_quot(jit_function_t f, u3_noun a)
{
  jit_value_t qot = _w(f, a);
  if ( _(u3a_is_dog(a)) ) {
    qot = _gain(f, qot);
  }
  return qot;
}

static jit_value_t
_ptr(jit_function_t f, void *p)
{
  return jit_value_create_nint_constant(f, jit_type_void_ptr, (jit_nint) p);
}

static jit_value_t
_off(jit_function_t f, jit_value_t a, jit_nint o)
{
  jit_value_t ptr = jit_insn_load_elem_address(f,
    _ptr(f, u3_Loom),
    jit_insn_and(f, a, _w(f, 0x3fffffff)),
    jit_type_uint);

  return jit_insn_load_relative(f, ptr, o, jit_type_uint);
}

static jit_value_t
_h(jit_function_t f, jit_value_t a)
{
  return _off(f, a, offsetof(u3a_cell, hed));
}

static jit_value_t
_t(jit_function_t f, jit_value_t a)
{
  return _off(f, a, offsetof(u3a_cell, tel));
}

static jit_value_t
_is_cell(jit_function_t f, jit_value_t a)
{
  return jit_insn_ne(f, _w(f, 3),
                     jit_insn_ushr(f, a, _w(f, 30)));
}

static void
_bail(jit_function_t f, jit_value_t wit)
{
  jit_insn_call_native(
    f, "u3m_bail", u3m_bail, _sig(c3n, 1), &wit, 1, JIT_CALL_NORETURN);
}

static jit_value_t
_eqw(jit_function_t f, jit_value_t one, c3_w two)
{
  return jit_insn_eq(f, one, _w(f, two));
}

static jit_value_t
_cell(jit_function_t f, jit_value_t a, jit_value_t b)
{
  return _nat(f, "[]", u3i_cell, c3y, 2, a, b);
}

static jit_value_t
_frag(jit_function_t f, u3_noun axe, jit_value_t bus)
{
  jit_label_t bal, fin;
  jit_value_t cur;
  u3_noun     exa;

  bal = fin = jit_label_undefined;
  cur = jit_insn_load(f, bus);

  while ( axe > 1 ) {
    jit_insn_branch_if_not(f, _eqw(f, _is_cell(f, bus), c3y), &bal);
    if ( 2 == u3qc_cap(axe) ) {
      jit_insn_store(f, cur, _h(f, cur));
    }
    else {
      jit_insn_store(f, cur, _t(f, cur));
    }
    exa = u3qc_mas(axe);
    u3z(axe);
    axe = exa;
  }

  jit_insn_branch(f, &fin);
  jit_insn_label(f, &bal);
  _bail(f, _w(f, c3__exit));
  jit_insn_label(f, &fin);

  return cur;
}

static jit_value_t
_nock_6(jit_function_t f, jit_value_t bus, u3_noun tys, u3_noun yes, u3_noun no)
{
  jit_label_t fin, alt;
  jit_value_t pro;

  fin = alt = jit_label_undefined;
  pro = jit_value_create(f, jit_type_uint);
  jit_insn_branch_if(f, _eqw(f, _nock(f, _gain(f, bus), tys), c3n), &alt);

  jit_insn_store(f, pro, _nock(f, bus, yes));
  jit_insn_branch(f, &fin);

  jit_insn_label(f, &alt);
  jit_insn_store(f, pro, _nock(f, bus, no));

  jit_insn_label(f, &fin);
  return pro;
}

static jit_value_t
_nock_9(jit_function_t f, jit_value_t bus, u3_noun axe, u3_noun cof)
{
  jit_label_t fin = jit_label_undefined;
  jit_value_t cor = _nock(f, bus, cof);
  jit_value_t jax = _quot(f, u3k(axe));
  jit_value_t pro = _nat(f, "u3j_kick", u3j_kick, c3y, 2, cor, jax);
  jit_value_t ruf;

  jit_insn_branch_if_not(f, _eqw(f, pro, u3_none), &fin);
  _lose(f, jax);
  ruf = _gain(f, _frag(f, axe, cor));
  jit_insn_store(f, pro, _nat(f, "*", u3n_nock_on, c3y, 2, cor, ruf));

  jit_insn_label(f, &fin);
  return pro;
}

static jit_value_t
_sing(jit_function_t f, jit_value_t a, jit_value_t b)
{
  return _nat(f, "=", u3r_sing, c3y, 2, a, b);
}

static jit_value_t
_surf(jit_function_t f)
{
  jit_value_t out, roa, rod;
  out = _ptr(f, &(u3H->rod_u));
  roa = _ptr(f, &u3R);
  rod = jit_insn_load_relative(f, roa, 0, jit_type_void_ptr);
  return jit_insn_eq(f, out, rod);
}

/* If you add a hint to _n_hint in nock.c, you most probably want to add hint
 * processing here as well.
*/
static jit_value_t
_nock_10(jit_function_t f, jit_value_t bus, u3_noun hif, u3_noun nex)
{
  u3_noun     zep;
  jit_value_t hod;

  if ( c3y == u3du(hif) ) {
    zep = u3h(hif);
    hod = _nock(f, _gain(f, bus), u3t(hif));
  }
  else {
    zep = hif;
    hod = _w(f, u3_nul);
  }

  switch ( zep ) {
    default:
      u3z(zep);
      _lose(f, hod);
      return _nock(f, bus, nex);

    case c3__hunk:
    case c3__lose:
    case c3__mean:
    case c3__spot: {
      jit_value_t pro, tmp;
      tmp = _cell(f, _w(f, zep), hod);
      _nat(f, "u3t_push", u3t_push, c3n, 1, tmp);
      pro = _nock(f, bus, nex);
      _nat(f, "u3t_drop", u3t_drop, c3n, 0);
      return pro;
    }

    case c3__live: {
      jit_label_t alt, fin;
      alt = fin = jit_label_undefined;

      jit_insn_branch_if(f, _eqw(f, _is_cell(f, hod), c3y), &alt);
      _nat(f, "u3t_heck", u3t_heck, c3n, 1, hod);
      jit_insn_branch(f, &fin);

      jit_insn_label(f, &alt);
      _lose(f, hod);

      jit_insn_label(f, &fin);
      return _nock(f, bus, nex);
    }

    case c3__slog: {
      if ( !(u3C.wag_w & u3o_quiet) ) {
        _nat(f, "u3t_slog", u3t_slog, c3n, 1, hod);
      }
      else {
        _lose(f, hod);
      }
      return _nock(f, bus, nex);
    }

    case c3__germ: {
      jit_value_t pro;
      jit_label_t alt, fin;

      alt = fin = jit_label_undefined;
      pro = _nock(f, bus, nex);

      jit_insn_branch_if_not(f, _eqw(f, _sing(f, pro, hod), c3y), &alt);
      _lose(f, pro);
      jit_insn_store(f, pro, hod);
      jit_insn_branch(f, &fin);

      jit_insn_label(f, &alt);
      _lose(f, hod);

      jit_insn_label(f, &fin);
      return pro;
    }

    case c3__fast: {
      jit_value_t pro = _nock(f, bus, nex);
      _nat(f, "u3j_mine", u3j_mine, c3n, 2, hod, _gain(f, pro));
      return pro;
    }

    case c3__memo: {
      jit_value_t pro, jnx;
      jit_label_t alt, fin;

      alt = fin = jit_label_undefined;
      _lose(f, hod);

      jnx = _quot(f, nex);
      pro = _nat(f, "u3z_find_2", u3z_find_2, c3y, 3,
        _w(f, c3__nock), bus, jnx);

      jit_insn_branch_if(f, _eqw(f, pro, u3_none), &alt);
      jit_insn_branch(f, &fin);

      jit_insn_label(f, &alt);
      jit_insn_store(f, pro, _nock(f, _gain(f, bus), nex));

      jit_insn_branch_if(f, _surf(f), &fin);
      _nat(f, "u3z_save_2", u3z_save_2, c3n, 4,
        _w(f, c3__nock), bus, jnx, pro);

      jit_insn_label(f, &fin);
      _lose(f, jnx);
      _lose(f, bus);

      return pro;
    }
  }
}

static jit_value_t
_nock_11(jit_function_t f, jit_value_t bus, u3_noun fer, u3_noun saf)
{
  jit_value_t ref, gof, val, pro;
  jit_label_t fin, kep;

  kep = fin = jit_label_undefined;
  ref = _nock(f, _gain(f, bus), fer);
  gof = _nock(f, bus, saf);
  val = _nat(f, "u3m_soft_esc", u3m_soft_esc, c3y, 2,
    ref, _gain(f, gof));

  jit_insn_branch_if(f, _eqw(f, _is_cell(f, val), c3y), &kep);
  _bail(f, _cell(f, _w(f, 1), _cell(f, gof, _w(f, 0))));

  jit_insn_label(f, &kep);
  jit_insn_branch_if(f, _eqw(f, _is_cell(f, _t(f, val)), c3y), &fin);

  _nat(f, "u3t_push", u3t_push, c3n, 2, _w(f, c3__hunk),
    _nat(f, "u3n_mush", u3n_mush, c3y, 1, gof));
  _bail(f, _w(f, c3__exit));

  jit_insn_label(f, &fin);
  pro = _gain(f, _t(f, _t(f, val)));
  _lose(f, gof);

  return pro;
}

/* _nock(): `fol` is RETAINED, `bus` is TRANSFERRED at runtime
*/
static jit_value_t
_nock(jit_function_t f, jit_value_t bus, u3_noun fol)
{
  jit_value_t pro, tmp;
  u3_noun     hib, gal;

  if ( c3n == u3du(fol) ) {
    u3m_bail(c3__exit);
  }

  hib = u3h(fol);
  gal = u3t(fol);

  if ( c3y == u3du(hib) ) {
    return _cell(f,
      _nock(f, _gain(f, bus), hib),
      _nock(f, bus, gal));
  }
  else switch ( hib ) {
    default: u3m_bail(c3__exit);
    case 0:
      return _gain(f, _frag(f, gal, bus));
    case 1:
      return _quot(f, u3k(gal));
    case 2:
      return _nat(f, "*", u3n_nock_on, c3y, 2,
        _nock(f, _gain(f, bus), u3h(gal)),
        _nock(f, bus, u3t(gal)));
    case 3:
      tmp = _nock(f, bus, gal);
      pro = _is_cell(f, tmp);
      _lose(f, tmp);
      return pro;
    case 4:
      return _nat(f, "+", u3i_vint, c3y, 1, _nock(f, bus, gal));
    case 5:
      tmp = _nock(f, bus, gal);
      pro = _sing(f, _h(f, tmp), _t(f, tmp));
      _lose(f, tmp);
      return pro;
    case 6:
      return _nock_6(f, bus, u3h(gal), u3h(u3t(gal)), u3t(u3t(gal)));
    case 7:
      tmp = _nock(f, bus, u3h(gal));
      return _nock(f, tmp, u3t(gal));
    case 8:
      tmp = _nock(f, _gain(f, bus), u3h(gal));
      return _nock(f, _cell(f, tmp, bus), u3t(gal));
    case 9:
      return _nock_9(f, bus, u3h(gal), u3t(gal));
    case 10:
      return _nock_10(f, bus, u3h(gal), u3t(gal));
    case 11:
      return _nock_11(f, bus, u3h(gal), u3t(gal));
  }
}

/* u3jit_compile(): compile a nock formula
*/
u3_funk
u3jit_compile(u3_noun fol) {
  jit_function_t f;
  jit_value_t    bus;

  c3_assert(u3R == &(u3H->rod_u));
  jit_context_build_start(cex);
  f   = jit_function_create(cex, _sig(c3y, 1));
  bus = _gain(f, jit_value_get_param(f, 0));
  if ( 0 ) {
    jit_value_t ruf = _quot(f, u3k(fol));
    jit_insn_return(f, _nat(f, "*", u3n_nock_on, c3y, 2, bus, ruf));
  }
  else {
    jit_insn_return(f, _nock(f, bus, fol));
  }
  jit_context_build_end(cex);
  jit_function_compile(f);
  return jit_function_to_closure(f);
}

void
u3jit_boot() {
  cex = jit_context_create();
}

/* _to functions operate on tomes and TRANSFER their arguments
 */
static u3_noun _to_pros(u3_noun, u3_noun);

static u3_noun
_to_chap(u3_noun nec)
{
  if ( u3_nul == nec ) {
    return u3_nul;
  }
  else if ( c3n == u3du(nec) ) {
    u3m_bail(c3__exit);
  }
  else {
    u3_noun pro = u3k(u3h(nec));
    u3z(nec);
    return pro;
  }
}

static u3_noun
_to_glue(u3_noun p, u3_noun q)
{
  if ( c3y == u3du(p) &&
       c3y == u3h(p)  &&
       c3y == u3du(q) &&
       c3y == u3h(q) )
  {
    u3_noun n = u3nc(u3k(u3t(p)), u3k(u3t(q)));
    u3z(p); u3z(q);
    return u3nc(c3y, n);
  }
  else {
    return u3nt(c3n, p, q);
  }
}

static u3_noun
_to_hiss(u3_noun nec)
{
  if ( u3_nul == nec ) {
    return u3_nul;
  }
  else if ( c3n == u3du(nec) ) {
    u3m_bail(c3__exit);
  }
  else {
    u3_noun pro = u3k(u3t(nec));
    u3z(nec);
    return pro;
  }
}

static u3_noun
_to_nec(u3_noun e)
{
  u3_noun nec = u3k(u3r_at(u3x_sam, e));
  u3z(e);
  return nec;
}

static u3_noun
_to_peek(u3_noun nec, u3_noun hec)
{
  if ( u3_nul == nec ) {
    u3z(hec);
    return u3_nul;
  }
  else if ( u3_nul == hec ) {
    return nec;
  }
  else {
    return _to_pros(nec, _to_hiss(hec));
  }
}

static u3_noun
_to_pros(u3_noun nec, u3_noun fut)
{
  if ( u3_nul == nec ) {
    u3z(fut);
    return u3_nul;
  }
  else if ( c3n == u3du(nec) ) {
    u3m_bail(c3__exit);
  }
  else {
    u3_noun pro = u3nc(u3k(u3h(nec)), fut);
    u3z(nec);
    return pro;
  }
}

static u3_noun
_to_seg(u3_noun a, u3_noun b)
{
  u3_noun i, tmp, pro;

  for ( pro = u3_none, i = b;
        u3_none != pro;
        tmp = u3qc_mas(a), u3z(a), a = tmp )
  {
    if ( 1 == a ) {
      pro = u3k(i);
    }
    else if ( u3_nul == i ) {
      pro = u3_nul;
    }
    else if ( c3n == u3du(i) ) {
      u3m_bail(c3__exit);
    }
    else if ( c3y == u3h(i) ) {
      pro = u3r_at(a, u3t(i));
      if ( u3_none == pro ) {
        u3m_bail(c3__exit);
      }
      else {
        pro = u3nc(c3y, u3k(pro));
      }
    }
  }

  u3z(a); u3z(b);
  return pro;
}

static u3_noun
_to_swap(u3_noun nec, u3_noun p)
{
  if ( u3_nul == nec || u3_nul == p ) {
    return u3_nul;
  }
  else {
    u3_noun pro = u3nc(p, u3k(u3t(nec)));
    u3z(nec);
    return pro;
  }
}

static u3_noun
_to_to(u3_noun e, u3_noun nec) {
  return u3i_molt(e, u3x_sam, nec, 0);
}

#if 0
static u3_noun
_to_bind(u3_noun nec, u3_noun t)
{
  u3_noun set, pro;
  if ( u3_nul == t ) {
    pro = u3_nul;
  }
  else {
    set = (u3_nul == nec)
        ? u3_nul
        : u3t(nec);
    pro = u3nc(u3k(u3h(t)), u3qdi_uni(set, u3t(t)));
  }
  u3z(nec); u3z(t);
  return pro;
}

static u3_noun
_to_auto(u3_noun nec, u3_noun pol, u3_noun qol)
{
  u3_noun hed, tal;
  hed = _to_nock(u3k(nec), pol);
  nec = _to_bind(u3k(hed), nec);
  tal = _to_nock(nec, qol);
  return _to_cons(hed, tal);
}

static u3_noun
_to_bump(u3_noun nec, u3_noun fol)
{
  u3_noun pro = _to_nock(nec, fol);

  if ( u3_nul == pro ) {
    return u3_nul;
  }
  else if ( c3y != u3h(u3h(pro)) || c3y == u3du(u3t(u3h(pro))) ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun a = u3i_vint(u3k(u3r_at(5, pro)));
    return u3i_molt(pro, 5, a, 0);
  }
}

static u3_noun
_to_cond(u3_noun nec, u3_noun tys, u3_noun yes, u3_noun no)
{
  u3_noun t = _to_nock(u3k(nec), tys);
  if ( u3_nul == t ) {
    u3z(nec); u3z(yes); u3z(no);
    return u3_nul;
  }
  else if ( c3y != u3h(u3h(t)) || u3t(u3h(t)) > 1 ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun pro;
    if ( c3y == u3t(u3h(t)) ) {
      pro = _to_nock(nec, yes);
      u3z(no);
    }
    else {
      pro = _to_nock(nec, no);
      u3z(yes);
    }
    return _to_bind(t, pro);
  }
}

static u3_noun
_to_comp(u3_noun nec, u3_noun sun, u3_noun fol)
{
  return _to_nock(_to_nock(nec, sun), fol);
}

static u3_noun
_to_deep(u3_noun nec, u3_noun fol)
{
  u3_noun pro = _to_nock(nec, fol);
  if ( u3_nul == pro ) {
    return u3_nul;
  }
  else if ( c3y == u3h(u3h(pro)) ) {
    c3_o ans_o = u3du(u3r_at(5, pro));
    return u3i_molt(pro, 5, ans_o, 0);
  }
  else {
    return u3i_molt(pro, 2, u3nc(c3y, c3y), 0);
  }
}

static u3_noun
_to_fake_in(u3_noun pag)
{
  if ( u3_nul == pag) {
    return 0;
  }
  else if ( c3y == u3h(pag) ) {
    return u3k(u3t(pag));
  }
  else {
    return u3nc(
      _to_fake_in(u3h(u3t(pag))),
      _to_fake_in(u3t(u3t(pag))));
  }
}

/* _to_fake: PRODUCE a real noun from a tome, where all the
 *           unknown pieces have been replaced by 0, and the
 *           known pieces are untagged. `nec` is RETAINED.
 */
static u3_noun
_to_fake(u3_noun nec)
{
  return (u3_nul == nec) ? 0 : _to_fake_in(u3h(nec));
}

static u3_noun
_to_fix(u3_noun nec, u3_noun sun, u3_noun fon)
{
  u3_noun net = _to_nock(u3k(nec), fon);
  if ( u3_nul == net || c3y != u3h(u3h(net)) ) {
    u3z(nec); u3z(sun); u3z(net);
    return u3_nul;
  }
  else {
    u3_noun fol = u3k(u3t(u3h(net)));
    nec = _to_bind(net, _to_nock(nec, sun));
    return _to_nock(nec, fol);
  }
}

static u3_noun
_to_frag(u3_noun nec, u3_noun a)
{
  u3_noun pro;
  if ( u3_nul == nec ) {
    pro = u3_nul;
  }
  else {
    c3_o    don_o = c3n;
    u3_noun i     = u3h(nec);
    while ( a > 1 ) {
      if ( u3_nul == i ) {
        pro = u3_nul;
        don_o = c3y;
        break;
      }
      else if ( c3y == u3h(i) ) {
        pro = u3nc(
          u3nc(c3y, u3k(u3r_at(a, u3t(i)))),
          u3k(u3t(nec)));
        don_o = c3y;
        break;
      }
      else {
        u3_noun b = u3qc_mas(a);
        i = (2 == u3qc_cap(a))
          ? u3h(u3t(i))
          : u3t(u3t(i));
        u3z(a);
        a = b;
      }
    }
    if ( c3n == don_o ) {
      pro = (u3_nul == i)
          ? u3_nul
          : u3nc(u3k(i), u3k(u3t(nec)));
    }
  }
  u3z(nec); u3z(a);
  return pro;
}

static u3_noun
_to_jot(u3_noun nec, u3_noun not)
{
  u3_noun inx, mor, pro;
  inx = u3qdi_wyt(u3t(nec));
  mor = u3qdi_put(u3t(nec), u3nc(inx, not));
  pro = u3nc(u3k(u3h(nec)), mor);
  u3z(nec);
  return pro;
}

static u3_noun
_to_hint(u3_noun nec, u3_noun hin, u3_noun nex)
{
  u3_noun pro, not;
  pro = _to_nock(u3k(nec), nex);
  if ( c3n == u3du(hin) ) {
    not = u3k(hin);
    u3z(nec);
  }
  else {
    u3_noun hit, pag;
    hit = _to_nock(nec, u3k(u3t(hin)));
    pag = (u3_nul == hit) ? u3_nul : u3k(u3h(hit));
    not = u3nc(u3k(u3h(hin)), pag);
    pro = _to_bind(hit, pro);
  }
  return _to_jot(pro, not);
}

static u3_noun
_to_kick(u3_noun nec, u3_noun axe, u3_noun con)
{
  u3_noun net, cot;
  cot = _to_nock(nec, con);
  net = _to_frag(u3k(cot), u3k(axe));
  if ( u3_nul == net || c3y != u3h(u3h(net)) ) {
    u3z(cot); u3z(net);
    return u3_nul;
  }
  else {
    u3_noun fak, pro;
    fak = _to_fake(nec);
    pro = u3j_kick(fak, axe);
    if ( u3_none != pro ) {
      pro = u3nc(u3nc(c3y, pro), u3k(u3t(cot)));
      u3z(cot);
    }
    else {
      pro = _to_nock(cot, u3k(u3t(u3h(net))));
      u3z(fak);
    }
    u3z(net); u3z(axe);
    return pro;
  }
}

static u3_noun
_to_push(u3_noun nec, u3_noun hen, u3_noun fol)
{
  u3_noun hed = _to_nock(u3k(nec), hen);
  return _to_nock(_to_cons(hed, nec), fol);
}

static u3_noun
_to_same(u3_noun nec, u3_noun a, u3_noun b)
{
  u3_noun c = _to_nock(nec, u3nc(a, b));

  if ( u3_nul == c || c3y != u3h(u3h(c)) ) {
    u3z(c);
    return u3_nul;
  }
  else {
    c3_o d_o = u3r_sing(u3h(u3t(u3h(c))), u3t(u3t(u3h(c))));
    return u3i_molt(c, 5, d_o, 0);
  }
}

static u3_noun
_to_nock(u3_noun nec, u3_noun fol)
{
  u3_noun hib, gal, pro, p, q, r;

  hib = u3h(fol);
  gal = u3t(fol);

  if ( c3y == u3du(hib) ) {
    pro = _to_auto(u3k(nec), u3k(hib), u3k(gal));
  }
  else switch (hib) {
    default:
      return u3m_bail(c3__exit);
    case 0:
      pro = _to_frag(u3k(nec), u3k(gal));
      break;
    case 1:
      pro = u3nc(u3nc(c3y, u3k(gal)), u3_nul);
      break;
    case 2:
      u3x_cell(gal, &p, &q);
      pro = _to_fix(u3k(nec), u3k(p), u3k(q));
      break;
    case 3:
      pro = _to_deep(u3k(nec), u3k(gal));
      break;
    case 4:
      pro = _to_bump(u3k(nec), u3k(gal));
      break;
    case 5:
      u3x_cell(gal, &p, &q);
      pro = _to_same(u3k(nec), u3k(p), u3k(q));
      break;
    case 6:
      u3x_trel(gal, &p, &q, &r);
      pro = _to_cond(u3k(nec), u3k(p), u3k(q), u3k(r));
      break;
    case 7:
      u3x_cell(gal, &p, &q);
      pro = _to_comp(u3k(nec), u3k(p), u3k(q));
      break;
    case 8:
      u3x_cell(gal, &p, &q);
      pro = _to_push(u3k(nec), u3k(p), u3k(q));
      break;
    case 9:
      u3x_cell(gal, &p, &q);
      pro = _to_kick(u3k(nec), u3k(p), u3k(q));
      break;
    case 10:
      u3x_cell(gal, &p, &q);
      pro = _to_hint(u3k(nec), u3k(p), u3k(q));
      break;
    case 11:
      pro = u3_nul;
      break;
  }

  return _to_bind(nec, pro);
}
#endif

/* u3jit_to functions are jets (and thus RETAIN) */

u3_noun
u3jit_tome_glue(u3_noun cor)
{
  u3_noun p, q;
  if ( c3n == u3r_mean(cor, u3x_sam_2, &p, u3x_sam_3, &q, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_glue(u3k(p), u3k(q));
  }
}
u3_noun
u3jit_tome_seg(u3_noun cor)
{
  u3_noun a, i;
  if ( c3n == u3r_mean(cor, u3x_sam_2, &a, u3x_sam_3, &i, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_seg(u3k(a), u3k(i));
  }
}

u3_noun
u3jit_to_auto(u3_noun cor)
{
  u3_noun e, pol, qol;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2, &pol,
        u3x_sam_3, &qol,
        u3x_con,   &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    //return _to_auto(u3k(nec), u3k(pol), u3k(qol));
    u3_noun nec = _to_nec(u3k(e));
    u3k(pol); u3k(qol);
    {
      u3_noun hed = u3n_slam_on(u3j_hook(u3k(e), "nock"), pol),
              hec = _to_nec(u3k(hed)),
              cen = _to_peek(nec, u3k(hec)),
              pek = u3i_molt(u3k(hed), u3x_sam, cen, 0),
              tal = u3n_slam_on(u3j_hook(pek, "nock"), qol),
              tec = _to_nec(u3k(tal)),
              goo = _to_glue(_to_chap(hec), _to_chap(u3k(tec)));
      return u3i_molt(tal, u3x_sam, _to_swap(tec, goo), 0);
    }
  }
}

u3_noun
u3jit_to_bump(u3_noun cor)
{
  u3_noun e, fol;

  if ( c3n == u3r_mean(cor, u3x_sam, &fol, u3x_con, &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen;
    u3k(fol);
    {
      u3_noun r, pro = _to_nec(u3n_slam_on(u3j_hook(u3k(e), "nock"), fol));
      if ( u3_nul == pro ) {
        r = u3_nul;
      }
      else if ( c3n == u3du(pro) ) {
        u3m_bail(c3__exit);
      }
      else {
        u3_noun n, p = u3h(pro);
        if ( c3n == u3du(p) || 
             c3y != u3h(p)  ||
             c3y == u3du(n = u3t(p)) ) 
        {
          u3m_bail(c3__exit);
        }
        else {
          r = u3nc(c3y, u3i_vint(n));
        }
      }
      cen = _to_swap(pro, r);
    }
    return u3i_molt(u3k(e), u3x_sam, cen, 0);
  }
}

u3_noun
u3jit_to_cond(u3_noun cor)
{
  u3_noun e, tys, yes, no;

  if ( c3n == u3r_mean(cor,
        u3x_sam_2, &tys,
        u3x_sam_6, &yes,
        u3x_sam_7, &no,
        u3x_con,   &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun nec = _to_nec(u3k(e));
    u3k(tys); u3k(yes); u3k(no);
 
    {
      u3_noun t = _to_nec(u3n_slam_on(u3j_hook(u3k(e), "nock"), tys));
      if ( u3_nul == t ) {
        u3z(nec); u3z(yes); u3z(no);
        return u3i_molt(u3k(e), u3x_sam, u3_nul, 0);
      }
      else if ( c3n == u3du(t)      ||
                c3n == u3du(u3h(t)) ||
                c3y != u3h(u3h(t))  ||
                u3t(u3h(t)) > 1 )
      {
        u3m_bail(c3__exit);
      }
      else {
        u3_noun cen, ne, fol, pag;
        cen = _to_pros(nec, u3k(u3t(t)));
        ne  = u3i_molt(u3k(e), u3x_sam, cen, 0);
        pag = u3h(t);
        if ( u3_nul == pag    ||
             c3n == u3du(pag) ||
             c3n == u3h(pag) )
        {
          u3m_bail(c3__exit);
        }
        else {
          u3_noun lob = u3t(pag);
          if ( c3y == lob ) {
            fol = yes;
            u3z(no);
          } 
          else if ( c3n == lob ) {
            fol = no;
            u3z(yes);
          }
          else {
            u3m_bail(c3__exit);
          }
        }
        return u3n_slam_on(u3j_hook(ne, "nock"), fol);
      }
    }
  }
}

u3_noun
u3jit_to_comp(u3_noun cor)
{
  u3_noun e, sun, fol;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2, &sun,
        u3x_sam_3, &fol,
        u3x_con,   &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun seb = u3n_slam_on(u3j_hook(u3k(e), "nock"), u3k(sun));
    return u3n_slam_on(u3j_hook(seb, "nock"), u3k(fol));
  }
}

u3_noun
u3jit_to_deep(u3_noun cor)
{
  u3_noun e, fol;

  if ( c3n == u3r_mean(cor, u3x_sam, &fol, u3x_con, &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen;
    u3k(fol);
    {
      u3_noun r, pro = _to_nec(u3n_slam_on(u3j_hook(u3k(e), "nock"), fol));
      if ( u3_nul == pro ) {
        r = u3_nul;
      }
      else if ( c3n == u3du(pro) ) {
        u3m_bail(c3__exit);
      }
      else {
        u3_noun p = u3h(pro);
        if ( c3n == u3du(p) ) {
          u3m_bail(c3__exit);
        }
        else if ( c3y == u3h(p) ) {
          r = u3nc(c3y, u3du(u3t(p)));
        }
        else if ( c3n == u3h(p) ) {
          r = u3nc(c3y, c3y);
        }
        else {
          u3m_bail(c3__exit);
        }
      }
      cen = _to_swap(pro, r);
    }
    return u3i_molt(u3k(e), u3x_sam, cen, 0);
  }
}

u3_noun
u3jit_to_fix(u3_noun cor)
{
  u3_noun e, sun, fon;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2, &sun,
        u3x_sam_3, &fon,
        u3x_con,   &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen, nec;
    u3m_p("fix", 0);
    nec = _to_nec(u3k(e));
    u3k(sun); u3k(fon);
    {
      u3_noun sen, en, nex, pag;
      sen = _to_nec(u3n_slam_on(u3j_hook(u3k(e), "nock"), sun));
      en  = _to_to(u3k(e), _to_peek(nec, u3k(sen)));
      nex = _to_nec(u3n_slam_on(u3j_hook(en, "nock"), fon));
      if ( u3_nul == nex ) {
        cen = u3_nul;
      }
      else if ( c3n == u3du(nex) ) {
        u3m_bail(c3__exit);
      }
      else if ( u3_nul == (pag = u3h(nex)) ) {
        cen = u3_nul;
      }
      else if ( c3n == u3du(pag) ) {
        u3m_bail(c3__exit);
      }
      else if ( c3n == u3h(pag) ) {
        cen = u3_nul;
      }
      else if ( c3y == u3h(pag) ) {
        en  = _to_to(u3k(e), _to_pros(sen, u3k(u3t(nex))));
        cen = _to_nec(u3n_slam_on(u3j_hook(en, "nock"), u3k(u3t(pag))));
      }
      else {
        u3m_bail(c3__exit);
      }
    }
    return _to_to(u3k(e), cen);
  }
}

u3_noun
u3jit_to_peek(u3_noun cor)
{
  u3_noun nec, e;
  if ( c3n == u3r_mean(cor, u3x_sam, &e, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen = _to_nec(u3k(e));
    if ( u3_none == cen ) {
      u3m_bail(c3__exit);
    }
    else {
      return u3i_molt(u3k(e), u3x_sam, _to_peek(u3k(nec), cen), 0);
    }
  }
}

u3_noun
u3jit_to_pros(u3_noun cor)
{
  u3_noun e, fut;
  if ( c3n == u3r_mean(cor, u3x_sam, &fut, u3x_con, &e, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen = _to_pros(_to_nec(u3k(e)), u3k(fut));
    return u3i_molt(u3k(e), u3x_sam, cen, 0);
  }
}

u3_noun
u3jit_to_same(u3_noun cor)
{
  u3_noun e, a, b;

  if ( c3n == u3r_mean(cor,
        u3x_sam_2, &a,
        u3x_sam_3, &b,
        u3x_con,   &e, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen;
    u3k(a); u3k(b);
    {
      u3_noun r, pro = _to_nec(u3n_slam_on(u3j_hook(u3k(e), "nock"), u3nc(a, b)));
      if ( u3_nul == pro ) {
        r = u3_nul;
      }
      else if ( c3n == u3du(pro) ) {
        u3m_bail(c3__exit);
      }
      else {
        u3_noun p = u3h(pro);
        if ( c3n == u3du(p) ) {
          u3m_bail(c3__exit);
        }
        else if ( c3y == u3h(p) ) {
          u3_noun n = u3t(p);
          if ( c3n == u3du(n) ) {
            u3m_bail(c3__exit);
          }
          else {
            r = u3nc(c3y, u3r_sing(u3h(n), u3t(n)));
          }
        }
        else {
          r = u3_nul;
        }
      }
      cen = _to_swap(pro, r);
    }
    return u3i_molt(u3k(e), u3x_sam, cen, 0);
  }
}

u3_noun
u3jit_to_swap(u3_noun cor)
{
  u3_noun e, p;
  if ( c3n == u3r_mean(cor, u3x_sam, &p, u3x_con, &e, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun cen = _to_swap(_to_nec(u3k(e)), u3k(p));
    return u3i_molt(u3k(e), u3x_sam, cen, 0);
  }
}

#if 0

u3_noun
u3jit_to_bind(u3_noun cor)
{
  u3_noun nec, t;
  if ( c3n == u3r_mean(cor, u3x_sam, &t, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  return _to_bind(u3k(nec), u3k(t));
}

u3_noun
u3jit_to_bump(u3_noun cor)
{
  u3_noun nec, fol;
  if ( c3n == u3r_mean(cor, u3x_sam, &fol, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_bump(u3k(nec), u3k(fol));
  }
}

u3_noun
u3jit_to_cons(u3_noun cor)
{
  u3_noun nec, t;
  if ( c3n == u3r_mean(cor, u3x_sam, &t, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_cons(u3k(nec), u3k(t));
  }
}

u3_noun
u3jit_to_deep(u3_noun cor)
{
  u3_noun nec, fol;
  if ( c3n == u3r_mean(cor, u3x_sam, &fol, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_deep(u3k(nec), u3k(fol));
  }
}

u3_noun
u3jit_to_fix(u3_noun cor)
{
  u3_noun nec, sun, fon;

  if ( c3n == u3r_mean(cor,
        u3x_sam_2,   &sun,
        u3x_sam_3,   &fon,
        u3x_con_sam, &nec, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_fix(u3k(nec), u3k(sun), u3k(fon));
  }
}

u3_noun
u3jit_to_frag(u3_noun cor)
{
  u3_noun nec, a;

  if ( c3n == u3r_mean(cor, u3x_sam, &a, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  return _to_frag(u3k(nec), u3k(a));
}

u3_noun
u3jit_to_jot(u3_noun cor)
{
  u3_noun nec, not;
  if ( c3n == u3r_mean(cor, u3x_sam, &not, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else if ( u3_nul == nec ) {
    return u3_nul;
  }
  else {
    return _to_jot(u3k(nec), u3k(not));
  }
}

u3_noun
u3jit_to_hint(u3_noun cor)
{
  u3_noun nec, hin, nex;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2,   &hin,
        u3x_sam_3,   &nex,
        u3x_con_sam, &nec, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_hint(u3k(nec), u3k(hin), u3k(nex));
  }
}

u3_noun
u3jit_to_kick(u3_noun cor)
{
  u3_noun nec, axe, con;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2,   &axe,
        u3x_sam_3,   &con,
        u3x_con_sam, &nec, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_kick(u3k(nec), u3k(axe), u3k(con));
  }
}

u3_noun
u3jit_to_nock(u3_noun cor)
{
  u3_noun nec, fol;

  if ( c3n == u3r_mean(cor, u3x_sam, &fol, u3x_con_sam, &nec, 0) ) {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_nock(u3k(nec), u3k(fol));
  }
}

u3_noun
u3jit_to_push(u3_noun cor)
{
  u3_noun nec, hen, fol;
  if ( c3n == u3r_mean(cor,
        u3x_sam_2,   &hen,
        u3x_sam_3,   &fol,
        u3x_con_sam, &nec, 0) )
  {
    return u3m_bail(c3__exit);
  }
  else {
    return _to_push(u3k(nec), u3k(hen), u3k(fol));
  }
}

#endif
