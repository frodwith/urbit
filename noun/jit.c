#include "all.h"
#include <jit/jit.h>

static jit_context_t cex;

static jit_value_t _nock(jit_function_t, jit_value_t, u3_noun);

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
