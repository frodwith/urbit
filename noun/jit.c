#include "all.h"
#include <jit/jit.h>

static jit_context_t cex;

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

static jit_value_t
_quot(jit_function_t f, u3_noun a)
{
  jit_value_t qot = _w(f, a);
  if ( _(u3a_is_dog(a)) ) {
    qot = _gain(f, qot);
  }
  return qot;
}

/* u3jit_compile(): compile a nock formula (trivial)
*/
u3_funk
u3jit_compile(u3_noun fol) {
  jit_function_t f;
  jit_value_t    bus, ruf;

  c3_assert(u3R == &(u3H->rod_u));
  jit_context_build_start(cex);
  f   = jit_function_create(cex, _sig(c3y, 1));
  bus = _gain(f, jit_value_get_param(f, 0));
  ruf = _quot(f, u3k(fol));
  jit_insn_return(f, _nat(f, "*", u3n_nock_on, c3y, 2, bus, ruf));
  jit_context_build_end(cex);
  jit_function_compile(f);
  return jit_function_to_closure(f);
}

void
u3jit_boot() {
  cex = jit_context_create();
}
