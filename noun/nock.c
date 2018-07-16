/* g/n.c
**
*/
#include "all.h"

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

// define to have each opcode printed as it executes,
// along with some other debugging info
#        undef VERBOSE_BYTECODE

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

#if 0
// Retained for debugging purposes.
static u3_noun _n_nock_on(u3_noun bus, u3_noun fol);

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
        u3_noun pro = u3z_find_2(144 + c3__nock, bus, nex);

        if ( pro != u3_none ) {
          u3z(bus); u3z(nex);
          return pro;
        }
        pro = _n_nock_on(u3k(bus), u3k(nex));

        if ( &(u3H->rod_u) != u3R ) {
          u3z_save_2(144 + c3__nock, bus, nex, pro);
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

/* _n_nock_on(): produce .*(bus fol).  Do not virtualize.
*/
static u3_noun
_n_nock_on(u3_noun bus, u3_noun fol)
{
  u3_noun hib, gal;

  while ( 1 ) {
    hib = u3h(fol);
    gal = u3t(fol);

#ifdef U3_CPU_DEBUG
    u3R->pro.nox_d += 1;
#endif

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
#endif

/* These must match the order in the section marked OPCODE TABLE,
 * and several opcodes "overflow" (from byte to short index) to
 * their successor, so order can matter here. */
// general purpose
#define HALT  0
#define BAIL  1
#define COPY  2
#define SWAP  3
#define TOSS  4
#define AUTO  5
#define AULT  6
#define SNOC  7
#define SNOL  8
#define HEAD  9
#define HELD 10
#define TAIL 11
#define TALL 12
// fragment (keep)
#define FABK 13
#define FASK 14
#define FIBK 15
#define FISK 16
// fragment (lose)
#define FABL 17
#define FASL 18
#define FIBL 19
#define FISL 20
// literal (keep)
#define LIT0 21
#define LIT1 22
#define LITB 23
#define LITS 24
#define LIBK 25
#define LISK 26
// literal (lose)
#define LIL0 27
#define LIL1 28
#define LILB 29
#define LILS 30
#define LIBL 31
#define LISL 32
// nock
#define NOLK 33
#define NOCT 34
#define NOCK 35
// 3 & 4
#define DEEP 36
#define BUMP 37
// equality
#define SAM0 38
#define SAM1 39
#define SAMB 40
#define SAMS 41
#define SANB 42
#define SANS 43
#define SAME 44
#define SALM 45
#define SAMC 46
// unconditional skips
#define SBIP 47
#define SIPS 48
#define SWIP 49
// conditional skips
#define SBIN 50
#define SINS 51
#define SWIN 52
// nock 9
#define KICB 53
#define KICS 54
#define TICB 55
#define TICS 56
// nock 11
#define WILS 57
#define WISH 58
// hint processing
#define BUSH 59
#define SUSH 60
#define DROP 61
#define HECK 62
#define SLOG 63
// fast (keep)
#define BAST 64
#define SAST 65
// fast (lose)
#define BALT 66
#define SALT 67
// memo (keep)
#define SKIB 68
#define SKIS 69
// memo (lose)
#define SLIB 70
#define SLIS 71
#define SAVE 72
// nock 12
#define MUTH 73
#define KUTH 74
#define MUTT 75
#define KUTT 76
#define MUSM 77
#define KUSM 78
#define MUTB 79
#define MUTS 80
#define MITB 81
#define MITS 82
#define KUTB 83
#define KUTS 84
#define KITB 85
#define KITS 86
#define LAST 87

/* _n_arg(): return the size (in bytes) of an opcode's argument
 */
static inline c3_y
_n_arg(c3_y cod_y)
{
  switch ( cod_y ) {
    case FABK: case FABL: case FIBL: case FIBK:
    case LILB: case LITB: case LIBL: case LIBK:
    case SAMB: case SANB: case SBIP: case SBIN:
    case SLIB: case SKIB: case KICB: case TICB:
    case BUSH: case BAST: case BALT:
    case MUTB: case KUTB: case MITB: case KITB:
      return sizeof(c3_y);

    case FASK: case FASL: case FISL: case FISK:
    case LILS: case LITS: case LISL: case LISK:
    case SAMS: case SANS: case SIPS: case SINS:
    case SLIS: case SKIS: case KICS: case TICS:
    case SUSH: case SAST: case SALT: 
    case MUTS: case KUTS: case MITS: case KITS:
      return sizeof(c3_s);

    case SWIP: case SWIN:
      return sizeof(c3_l);

    default:
      c3_assert( cod_y < LAST );
      return 0;
  }
}


/* _n_melt(): measure space for list of ops (from _n_comp) */
static u3_noun
_n_melt(u3_noun ops, c3_w* byc_w, c3_w* cal_w,
        c3_w* reg_w, c3_w* lit_w, c3_w* mem_w)
{
  c3_w len_w = u3qb_lent(ops),
       i_w = len_w - 1,
       a_w;
  c3_y cod_y;
  c3_y* siz_y = u3a_malloc(len_w);
  u3_noun op, sip = u3_nul;

  while ( u3_nul != ops ) {
    op  = u3h(ops);
    if ( c3n == u3du(op) ) {
      switch ( op ) {
        default:
          siz_y[i_w] = 1;
          break;

        case BAST: case BALT:
          a_w = (*reg_w)++;
          if ( a_w <= 0xFF ) {
            siz_y[i_w] = 2;
          }
          else if ( a_w <= 0xFFFF ) {
            siz_y[i_w] = 3;
          }
          else {
            fprintf(stderr, "_n_melt(): over 2^16 registration sites.\r\n");
            c3_assert(0);
          }
          break;
      }
    }
    else {
      cod_y = u3h(op);

      switch ( cod_y ) {
        default:
          siz_y[i_w] = 1 + _n_arg(cod_y);
          break;

        case SBIP: case SBIN: {
          c3_l tot_l = 0,
               sip_l = u3t(op);
          c3_w j_w, k_w = i_w;
          for ( j_w = 0; j_w < sip_l; ++j_w ) {
            tot_l += siz_y[++k_w];
          }
          sip = u3nc(tot_l, sip);
          siz_y[i_w] = tot_l <= 0xFF ? 2 : tot_l <= 0xFFFF ? 3 : 5;
          break;
        }

        case SKIB: case SLIB: {
          c3_l tot_l = 0,
               sip_l = u3h(u3t(op));
          c3_w j_w, k_w = i_w;
          for ( j_w = 0; j_w < sip_l; ++j_w ) {
            tot_l += siz_y[++k_w];
          }
          sip = u3nc(tot_l, sip);
          a_w = (*mem_w)++;
          if ( a_w <= 0xFF ) {
            siz_y[i_w] = 2;
          }
          else if ( a_w <= 0xFFFF ) {
            siz_y[i_w] = 3;
          }
          else {
            fprintf(stderr, "_n_melt(): over 2^16 memos.\r\n");
            c3_assert(0);
          }
          break;
        }

        case SIPS: case SINS: case SWIP: case SWIN:
        case SAST: case SALT: case KICS: case TICS:
        case FISK: case FISL: case SUSH: case SANS:
        case LISL: case LISK: case SKIS: case SLIS:
          c3_assert(0); //overflows
          break;

        case KICB: case TICB:
          a_w = (*cal_w)++;
          if ( a_w <= 0xFF ) {
            siz_y[i_w] = 2;
          }
          else if ( a_w <= 0xFFFF ) {
            siz_y[i_w] = 3;
          }
          else {
            fprintf(stderr, "_n_melt(): over 2^16 call sites.\r\n");
            c3_assert(0);
          }
          break;
        
        case BUSH: case FIBK: case FIBL:
        case SANB: case LIBL: case LIBK:
        case KITB: case MITB:
          a_w = (*lit_w)++;
          if ( a_w <= 0xFF ) {
            siz_y[i_w] = 2;
          }
          else if ( a_w <= 0xFFFF ) {
            siz_y[i_w] = 3;
          }
          else {
            fprintf(stderr, "_n_melt(): over 2^16 literals.\r\n");
            c3_assert(0);
          }
          break;
      }
    }

    *(byc_w) += siz_y[i_w--];
    ops = u3t(ops);
  }

  u3a_free(siz_y);
  return u3kb_flop(sip);
}

/* _n_prog_dat(): return pointer to program's data segment
 */
static void*
_n_prog_dat(u3n_prog* pog_u)
{
  return ((void*) pog_u) + sizeof(u3n_prog);
}

/* _n_prog_new(): allocate and set up pointers for u3n_prog
 */
static u3n_prog*
_n_prog_new(c3_w byc_w, c3_w cal_w,
            c3_w reg_w, c3_w lit_w, c3_w mem_w)
{
  c3_w cab_w = (sizeof(u3j_site) * cal_w),
       reb_w = (sizeof(u3j_rite) * reg_w),
       lib_w = (sizeof(u3_noun) * lit_w),
       meb_w = (sizeof(u3n_memo) * mem_w),
       dat_w = byc_w + cab_w + reb_w + lib_w + meb_w;

  u3n_prog* pog_u     = u3a_malloc(sizeof(u3n_prog) + dat_w);
  pog_u->byc_u.own_o = c3y;
  pog_u->byc_u.len_w = byc_w;
  pog_u->byc_u.ops_y = (c3_y*) _n_prog_dat(pog_u);

  pog_u->lit_u.len_w = lit_w;
  pog_u->lit_u.non   = (u3_noun*) (pog_u->byc_u.ops_y + pog_u->byc_u.len_w);

  pog_u->mem_u.len_w = mem_w;
  pog_u->mem_u.sot_u = (u3n_memo*) (pog_u->lit_u.non + pog_u->lit_u.len_w);

  pog_u->cal_u.len_w = cal_w;
  pog_u->cal_u.sit_u = (u3j_site*) (pog_u->mem_u.sot_u + pog_u->mem_u.len_w);

  pog_u->reg_u.len_w = reg_w;
  pog_u->reg_u.rit_u = (u3j_rite*) (pog_u->cal_u.sit_u + pog_u->cal_u.len_w);

  return pog_u;
}

/* _n_prog_old(): as _n_prog_new(),
 *                but leech off senior program's data segment
 */
static u3n_prog*
_n_prog_old(u3n_prog* sep_u)
{
  c3_w cab_w = sizeof(u3j_site) * sep_u->cal_u.len_w,
       reb_w = sizeof(u3j_rite) * sep_u->reg_u.len_w,
       lib_w = sizeof(u3_noun) * sep_u->lit_u.len_w,
       meb_w = sizeof(u3n_memo) * sep_u->mem_u.len_w,
       dat_w = cab_w + reb_w + lib_w + meb_w;

  u3n_prog* pog_u    = u3a_malloc(sizeof(u3n_prog) + dat_w);

  pog_u->cap_w       = sep_u->cap_w;
  pog_u->byc_u.own_o = c3n;
  pog_u->byc_u.len_w = sep_u->byc_u.len_w;
  pog_u->byc_u.ops_y = sep_u->byc_u.ops_y;

  pog_u->lit_u.len_w = sep_u->lit_u.len_w;
  pog_u->lit_u.non   = (u3_noun*) _n_prog_dat(pog_u);

  pog_u->mem_u.len_w = sep_u->mem_u.len_w;
  pog_u->mem_u.sot_u = (u3n_memo*) (pog_u->lit_u.non + pog_u->lit_u.len_w);

  pog_u->cal_u.len_w = sep_u->cal_u.len_w;
  pog_u->cal_u.sit_u = (u3j_site*) (pog_u->mem_u.sot_u + pog_u->mem_u.len_w);

  pog_u->reg_u.len_w = sep_u->reg_u.len_w;
  pog_u->reg_u.rit_u = (u3j_rite*) (pog_u->cal_u.sit_u + pog_u->cal_u.len_w);

  memcpy(pog_u->lit_u.non, sep_u->lit_u.non, dat_w);
  return pog_u;
}

/* _n_prog_asm_inx(): write an index to the bytestream with overflow
 */
static void
_n_prog_asm_inx(c3_y* buf_y, c3_w* i_w, c3_s inx_s, c3_y cod)
{
  if ( inx_s <= 0xFF ) {
    buf_y[(*i_w)--] = (c3_y) (inx_s);
    buf_y[*i_w]     = (c3_y) cod;
  }
  else {
    buf_y[(*i_w)--] = (c3_y) (inx_s >> 8);
    buf_y[(*i_w)--] = (c3_y) (inx_s);
    // the short-index versions of these opcodes must immediately
    // follow the byte-index versions because of this convention
    buf_y[(*i_w)]   = cod + 1;
  }
}

#ifdef VERBOSE_BYTECODE
// match to OPCODE TABLE
static char* opcode_names[] = {
  "halt", "bail",
  "copy", "swap", "toss",
  "auto", "ault", "snoc", "snol",
  "head", "held", "tail", "tall",
  "fabk", "fask", "fibk", "fisk",
  "fabl", "fasl", "fibl", "fisl",
  "lit0", "lit1", "litb", "lits",
  "libk", "lisk",
  "lil0", "lil1", "lilb", "lils",
  "libl", "lisl",
  "nolk", "noct", "nock",
  "deep", "bump",
  "sam0", "sam1", "samb", "sams",
  "sanb", "sans",
  "same", "salm", "samc",
  "sbip", "sips", "swip",
  "sbin", "sins", "swin",
  "kicb", "kics", "ticb", "tics",
  "wils", "wish",
  "bush", "sush",
  "drop", "heck", "slog",
  "bast", "sast",
  "balt", "salt",
  "skib", "skis", "slib", "slis",
  "save",
  "muth", "kuth", "mutt", "kutt",
  "musm", "kusm",
  "mutb", "muts", "mitb", "mits",
  "kutb", "kuts", "kitb", "kits",
};
#endif

//static void _n_print_byc(c3_y* pog, c3_w her_w);

//static c3_t opcode_seen[LAST];

/* _n_prog_asm(): assemble list of ops (from _n_comp) into u3n_prog
 */
static void
_n_prog_asm(u3_noun ops, u3n_prog* pog_u, u3_noun sip)
{
  u3_noun top    = ops;
  c3_y*   buf_y  = pog_u->byc_u.ops_y;
  c3_s    lit_s  = 0,
          cal_s  = 0,
          mem_s  = 0,
          reg_s  = 0;
  c3_w    i_w    = pog_u->byc_u.len_w-1;

  buf_y[i_w] = HALT;

  while ( i_w-- > 0 ) {
    u3_noun op = u3h(ops);
    if ( c3y == u3ud(op) ) {
      switch ( op ) {
        default:
          buf_y[i_w] = (c3_y) u3h(ops);
          break;

        /* registration site index args */
        case BAST: case BALT: {
          _n_prog_asm_inx(buf_y, &i_w, reg_s, op);
          u3j_rite* rit_u = &(pog_u->reg_u.rit_u[reg_s++]);
          rit_u->own_o = c3n;
          rit_u->clu   = u3_none;
          rit_u->fin_p = 0;
          break;
        }
      }
    }
    else {
      u3_noun cod = u3h(op);
      switch ( cod ) {
        default:
          c3_assert(0);
          return;

        /* memo index args */
        case SKIB: case SLIB: {
          u3n_memo* mem_u;
          c3_l sip_l  = u3h(sip);
          u3_noun tmp = sip;
          sip = u3k(u3t(sip));
          u3z(tmp);
          _n_prog_asm_inx(buf_y, &i_w, mem_s, cod);
          mem_u        = &(pog_u->mem_u.sot_u[mem_s++]);
          mem_u->sip_l = sip_l;
          mem_u->key   = u3k(u3t(u3t(op)));
          break;
        }

        /* skips */
        case SBIP: case SBIN: {
          c3_l sip_l  = u3h(sip);
          u3_noun tmp = sip;
          sip = u3k(u3t(sip));
          u3z(tmp);
          if ( sip_l <= 0xFF ) {
            buf_y[i_w--] = (c3_y) sip_l;
            buf_y[i_w]   = (c3_y) cod;
          }
          else if ( sip_l <= 0xFFFF ) {
            buf_y[i_w--] = (c3_y) (sip_l >> 8);
            buf_y[i_w--] = (c3_y) sip_l;
            buf_y[i_w]   = (c3_y) cod + 1;
          }
          else {
            buf_y[i_w--] = (c3_y) (sip_l >> 24);
            buf_y[i_w--] = (c3_y) (sip_l >> 16);
            buf_y[i_w--] = (c3_y) (sip_l >> 8);
            buf_y[i_w--] = (c3_y) sip_l;
            buf_y[i_w]   = (c3_y) cod + 2;
          }
          break;
        }

        /* 8-bit direct args */
        case FABK: case FABL:
        case LITB: case LILB: 
        case MUTB: case KUTB:
        case SAMB: 
          buf_y[i_w--] = (c3_y) u3t(op);
          buf_y[i_w]   = (c3_y) cod;
          break;

        /* 16-bit direct args */
        case FASK: case FASL:
        case LILS: case LITS:
        case MUTS: case KUTS:
        case SAMS: case SIPS: case SINS: {
          c3_s off_s   = u3t(op);
          buf_y[i_w--] = (c3_y) (off_s >> 8);
          buf_y[i_w--] = (c3_y) off_s;
          buf_y[i_w]   = (c3_y) cod;
          break;
        }

        /* 31-bit direct args */
        case SWIP: case SWIN: {
          c3_w off_l   = u3t(op);
          buf_y[i_w--] = (c3_y) (off_l >> 24);
          buf_y[i_w--] = (c3_y) (off_l >> 16);
          buf_y[i_w--] = (c3_y) (off_l >> 8);
          buf_y[i_w--] = (c3_y) off_l;
          buf_y[i_w]   = (c3_y) cod;
          break;
        }

        /* literal index args */
        case FIBK: case FIBL: 
        case LIBK: case LIBL:
        case BUSH: case SANB:
        case KITB: case MITB:
          _n_prog_asm_inx(buf_y, &i_w, lit_s, cod);
          pog_u->lit_u.non[lit_s++] = u3k(u3t(op));
          break;

        /* call site index args */
        case TICB: case KICB: {
          _n_prog_asm_inx(buf_y, &i_w, cal_s, cod);
          u3j_site* sit_u = &(pog_u->cal_u.sit_u[cal_s++]);
          sit_u->axe   = u3k(u3t(op));
          sit_u->pog_p = 0;
          sit_u->bat   = u3_none;
          sit_u->bas   = u3_none;
          sit_u->loc   = u3_none;
          sit_u->lab   = u3_none;
          sit_u->jet_o = c3n;
          sit_u->fon_o = c3n;
          sit_u->cop_u = NULL;
          sit_u->ham_u = NULL;
          sit_u->fin_p = 0;
          break;
        }
      }
    }
    ops    = u3t(ops);
  }
  u3z(top);
#ifdef U3_CPU_DEBUG
  // this assert will fail if we overflow a c3_w worth of instructions
  c3_assert(u3_nul == ops);
  // sanity checks
  c3_assert(u3_nul == sip);
  //c3_assert(1 == s_ws);
#endif
}

/* _n_prog_from_ops(): new program from _n_comp() product
 */
static u3n_prog*
_n_prog_from_ops(u3_noun ops, c3_w cap_w)
{
  u3_noun sip;
  u3n_prog* pog_u;
  c3_w byc_w = 1, // HALT
       cal_w = 0,
       reg_w = 0,
       lit_w = 0,
       mem_w = 0;

  sip   = _n_melt(ops, &byc_w, &cal_w, &reg_w, &lit_w, &mem_w);
  pog_u = _n_prog_new(byc_w, cal_w, reg_w, lit_w, mem_w);
  _n_prog_asm(ops, pog_u, sip);
  pog_u->cap_w = cap_w;
  return pog_u;
}

#if 0
/* _n_print_stack(): print out the cap stack up to a designated "empty"
 *                   used only for debugging
 */
static void _n_print_stack(u3p(u3_noun) empty) {
  c3_w cur_p = u3R->cap_p;
  fprintf(stderr, "[");
  int first = 1;
  while ( cur_p != empty ) {
    if ( first ) {
      first = 0;
    }
    else {
      fprintf(stderr, " ");
    }
    if ( c3y == u3a_is_north(u3R) ) {
      fprintf(stderr, "%u", *(u3to(u3_noun, cur_p)));
      cur_p++;
    }
    else {
      fprintf(stderr, "%u", *(u3to(u3_noun, cur_p-1)));
      cur_p--;
    }
  }
  fprintf(stderr, "]\r\n");
}
#endif

/* _n_apen(): emit the instructions contained in src to dst
 */
static inline void
_n_apen(u3_noun* dst, u3_noun src)
{
  *dst = u3kb_weld(src, *dst);
}

/* _n_emit(): emit a single instruction to ops
 */
static inline void
_n_emit(u3_noun *ops, u3_noun op)
{
  *ops = u3nc(op, *ops);
}

static c3_w _n_comp(u3_noun*, c3_w*, c3_w*, u3_noun, c3_o, c3_o);

/* _n_bint(): hint-processing helper for _n_comp.
 *            hif: hint-formula (first part of 10). RETAIN.
 *            nef: next-formula (second part of 10). RETAIN.
 */
static c3_w
_n_bint(u3_noun* ops, c3_w* sp_w, c3_w* cap_w,
        u3_noun hif, u3_noun nef, c3_o los_o, c3_o tel_o)
{
  if ( c3n == u3du(hif) ) {
    // no currently recognized static hints
    return _n_comp(ops, sp_w, cap_w, nef, los_o, tel_o);
  }
  else {
    c3_w tot_w = 0;
    u3_noun zep, hod;
    u3x_cell(hif, &zep, &hod);

    switch ( zep ) {
      default:
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, TOSS);
        --*sp_w;
        tot_w += _n_comp(ops, sp_w, cap_w, nef, los_o, tel_o);
        break;

      case c3__hunk:
      case c3__lose:
      case c3__mean:
      case c3__spot:
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, u3nc(BUSH, zep)); // overflows to SUSH
        --*sp_w;
        tot_w += _n_comp(ops, sp_w, cap_w, nef, los_o, c3n);
        ++tot_w; _n_emit(ops, DROP);
        break;

      case c3__live:
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, HECK);
        --*sp_w;
        tot_w += _n_comp(ops, sp_w, cap_w, nef, los_o, tel_o);
        break;

      case c3__slog:
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, SLOG);
        --*sp_w;
        tot_w += _n_comp(ops, sp_w, cap_w, nef, los_o, tel_o);
        break;

      // germ and sole are unused...

      case c3__fast:
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, SWAP);
        tot_w += _n_comp(ops, sp_w, cap_w, nef, c3n, c3n);
        // overflows to SALT / SAST
        ++tot_w; _n_emit(ops, (c3y == los_o) ? BALT : BAST);
        *sp_w -= ( c3y == los_o ) ? 2 : 1;
        break;

      case c3__memo: {
        u3_noun mem = u3_nul;
        c3_w mem_w = 0;
        c3_y op_y;

        // we just throw away the hint (why is this not a static hint?)
        tot_w += _n_comp(ops, sp_w, cap_w, hod, c3n, c3n);
        ++tot_w; _n_emit(ops, TOSS);

        // not popping after toss gives space for the key
        if ( c3n == los_o ) {
          // space for copied subject
          ++*sp_w;
        }

        // memoizing code always loses TOS because SAVE needs [pro key]
        mem_w += _n_comp(&mem, sp_w, cap_w, nef, c3y, c3n);
        ++mem_w; _n_emit(&mem, SAVE);

        --*sp_w; // save pop

        op_y   = (c3y == los_o) ? SLIB : SKIB; // overflows to SLIS / SKIS
        ++tot_w; _n_emit(ops, u3nt(op_y, mem_w, u3k(nef)));
        tot_w += mem_w; _n_apen(ops, mem);
        break;
      }
    }
    return tot_w;
  }
}

/* _n_weigh_to(): _n_print_helper to determine what a "large" constant is
 */
/*
static c3_w
_n_weigh_to(u3_noun som, c3_w max_w)
{
  if ( c3y == u3ud(som) ) {
    return 1;
  }
  else {
    c3_w hed_w = _n_weigh_to(u3h(som), max_w);
    if ( hed_w == max_w ) {
      return max_w;
    }
    else {
      c3_w tel_w = _n_weigh_to(u3t(som), max_w - hed_w);
      return c3_max(max_w, hed_w + tel_w);
    }
  }
}
*/

/* _n_print(): pretty-print a nock formula, eliding large constants
 */
/*
static void
_n_print(u3_noun fol, c3_o tel_o)
{
  u3_noun op, arg;
  u3x_cell(fol, &op, &arg);
  if ( c3n == tel_o ) {
    fprintf(stderr, "[");
  }
  if ( c3y == u3du(op) ) {
    _n_print(op, c3n);
    fprintf(stderr, " ");
    _n_print(arg, c3y);
  }
  else {
    fprintf(stderr, "%%");
    c3_c* str;
    switch ( op ) {
      default:
        c3_assert(0);
        break;

      case 0:
        str = u3m_pretty(arg);
        fprintf(stderr, "0 %s", str);
        free(str);
        break;

      case 1:
        if ( 33 == _n_weigh_to(arg, 33) ) {
          fprintf(stderr, "1 <<snip>>");
        }
        else {
          str = u3m_pretty(arg);
          fprintf(stderr, "1 %s", str);
          free(str);
        }
        break;

      case 2:
      case 7:
      case 8:
      case 11:
        fprintf(stderr, "%d ", op);
        _n_print(u3h(arg), c3n);
        fprintf(stderr, " ");
        _n_print(u3t(arg), c3y);
        break;

      case 3:
      case 4:
      case 5:
        fprintf(stderr, "%d ", op);
        _n_print(arg, c3y);
        break;

      case 6:
        fprintf(stderr, "6 ");
        _n_print(u3h(arg), c3n);
        fprintf(stderr, " ");
        _n_print(u3h(u3t(arg)), c3n);
        fprintf(stderr, " ");
        _n_print(u3t(u3t(arg)), c3y);
        break;

      case 9:
        str = u3m_pretty(u3h(arg));
        fprintf(stderr, "9 %s ", str);
        free(str);
        _n_print(u3t(arg), c3y);
        break;

      case 10:
        fprintf(stderr, "10 ");
        if ( c3y == u3du(u3h(arg)) ) {
          str = u3m_pretty(u3h(u3h(arg)));
          fprintf(stderr, "[%s ", str);
          free(str);
          _n_print(u3t(u3h(arg)), c3y);
          fprintf(stderr, "] ");
        }
        else {
          str = u3m_pretty(u3h(arg));
          fprintf(stderr, "%s ", str);
          free(str);
        }
        _n_print(u3t(arg), c3y);
        break;

      case 12:
        str = u3m_pretty(u3h(u3h(arg)));
        fprintf(stderr, "12 [%s ", str);
        free(str);
        _n_print(u3t(u3h(arg)), c3y);
        fprintf(stderr, "] ");
        _n_print(u3t(arg), c3y);
        break;
    }
  }
  if ( c3n == tel_o ) {
    fprintf(stderr, "]");
  }
}
*/

/* _n_comp(): compile nock formula to reversed opcode list
 *            ops is a pointer to a list (to be emitted to)
 *            sp_w and cap_w are used to track stack depth
 *            fol is the nock formula to compile. RETAIN.
 *            los_o indicates whether we should remove our
 *                  subject from the stack
 *            tel_o is yes if this formula is in tail position
 *            return: number of instructions added to the opcode list
 */
static c3_w
_n_comp(u3_noun* ops, c3_w* sp_w, c3_w* cap_w,
        u3_noun fol, c3_o los_o, c3_o tel_o)
{
  c3_y op_y;
  c3_w tot_w = 0;
  u3_noun cod, arg, hed, tel;
  u3x_cell(fol, &cod, &arg);

  if ( c3y == u3du(cod) ) {
    tot_w += _n_comp(ops, sp_w, cap_w, cod, c3n, c3n);
    ++tot_w; _n_emit(ops, SWAP);
    tot_w += _n_comp(ops, sp_w, cap_w, arg, c3n, c3n);
    ++tot_w; _n_emit(ops, ( c3y == los_o ) ? AULT : AUTO);
    *sp_w -= ( c3y == los_o ) ? 2 : 1;
  }
  else switch ( cod ) {
    case 0:
      if ( c3n == los_o ) {
        ++*sp_w;
        *cap_w = c3_max(*sp_w, *cap_w);
      }
      if ( c3n == u3ud(arg) ) {
        u3m_bail(c3__exit);
        return 0;
      }
      switch ( arg ) {
        case 0:
          ++tot_w; _n_emit(ops, BAIL);
          break;
        case 1:
          if ( c3n == los_o ) {
            ++tot_w; _n_emit(ops, COPY);
          }
          break;
        case 2:
          ++tot_w; _n_emit(ops, (c3y == los_o) ? HELD : HEAD);
          break;
        case 3:
          ++tot_w; _n_emit(ops, (c3y == los_o) ? TALL : TAIL);
          break;
        default:
          op_y = (c3y == los_o)
               ? (arg <= 0xFF ? FABL : arg <= 0xFFFF ? FASL : FIBL)  // overflows to FISL
               : (arg <= 0xFF ? FABK : arg <= 0xFFFF ? FASK : FIBK); // overflows to FISK
          ++tot_w; _n_emit(ops, u3nc(op_y, arg));
          break;
      }
      break;

    case 1:
      if ( c3n == los_o ) {
        ++*sp_w;
        *cap_w = c3_max(*sp_w, *cap_w);
      }
      switch ( arg ) {
        case 0:
          ++tot_w; _n_emit(ops, (c3y == los_o) ? LIL0 : LIT0);
          break;
        case 1:
          ++tot_w; _n_emit(ops, (c3y == los_o) ? LIL1 : LIT1);
          break;
        default:
          op_y = (c3y == los_o)
               ? (arg <= 0xFF ? LILB : arg <= 0xFFFF ? LILS : LIBL)  // overflows to LISL
               : (arg <= 0xFF ? LITB : arg <= 0xFFFF ? LITS : LIBK); // overflows to LISK
          ++tot_w; _n_emit(ops, u3nc(op_y, u3k(arg)));
          break;
      }
      break;

    case 2:
      u3x_cell(arg, &hed, &tel);
      tot_w += _n_comp(ops, sp_w, cap_w, hed, c3n, c3n);
      ++tot_w; _n_emit(ops, SWAP);
      tot_w += _n_comp(ops, sp_w, cap_w, tel, c3n, c3n);
      /* things in tail position replace (so, lose) top of stack,
       * so NOCT "loses" and there is no non-losing version */
      op_y   = (c3y == tel_o)  ? NOCT
             : ((c3y == los_o) ? NOLK : NOCK);
      ++tot_w; _n_emit(ops, op_y);
      *sp_w -= ( NOCK == op_y ) ? 1 : 2;
      break;

    case 3:
      tot_w += _n_comp(ops, sp_w, cap_w, arg, los_o, c3n);
      ++tot_w; _n_emit(ops, DEEP);
      break;

    case 4:
      tot_w += _n_comp(ops, sp_w, cap_w, arg, los_o, c3n);
      ++tot_w; _n_emit(ops, BUMP);
      break;

    case 5: {
      u3x_cell(arg, &hed, &tel);

      if ( c3n == u3du(hed) ) {
        tot_w += _n_comp(ops, sp_w, cap_w, arg, los_o, c3n);
        ++tot_w; _n_emit(ops, SAMC);
      }
      else {
        c3_t hec_t, tec_t;
        hec_t = (1 == u3h(hed));
        if ( c3n == u3du(tel) ) {
          u3m_bail(c3__exit);
          break;
        }
        else {
          tec_t = (1 == u3h(tel));
        }
        if ( hec_t && tec_t ) {
          if ( c3y == u3r_sing(u3t(hed), u3t(tel)) ) {
            ++tot_w; _n_emit(ops, (c3y == los_o) ? LIL0 : LIT0);
          }
          else {
            ++tot_w; _n_emit(ops, (c3y == los_o) ? LIL1 : LIT1);
          }
          if ( c3n == los_o ) {
            ++*sp_w;
          }
        }
        else if ( !hec_t && !tec_t ) {
          tot_w += _n_comp(ops, sp_w, cap_w, hed, c3n, c3n);
          ++tot_w; _n_emit(ops, SWAP);
          tot_w += _n_comp(ops, sp_w, cap_w, tel, c3n, c3n);
          ++tot_w; _n_emit(ops, (c3y == los_o) ? SALM : SAME);
          *sp_w -= ( c3y == los_o ) ? 2 : 1;
        }
        else {
          tot_w += _n_comp(ops, sp_w, cap_w, (hec_t ? tel : hed), los_o, c3n);
          u3_noun lit = u3t(hec_t ? hed : tel);
          switch ( lit ) {
            case 0:
              ++tot_w; _n_emit(ops, SAM0);
              break;
            case 1:
              ++tot_w; _n_emit(ops, SAM1);
              break;
            default:
              // overflows to SANS
              op_y = lit <= 0xFF ? SAMB : lit <= 0xFFFF ? SAMS : SANB;
              ++tot_w; _n_emit(ops, u3nc(op_y, u3k(lit)));
          }
        }
      }
      break;
    }

    case 6: {
      u3_noun mid,
              yep = u3_nul,
              nop = u3_nul;
      c3_w    yep_w, nop_w;
      u3x_trel(arg, &hed, &mid, &tel);
      tot_w += _n_comp(ops, sp_w, cap_w, hed, c3n, c3n);
      --*sp_w; // pop the test
      yep_w  = _n_comp(&yep, sp_w, cap_w, mid, los_o, tel_o);
      if ( c3n == los_o ) {
        // pop leftover from yes branch
        --*sp_w;
      }
      nop_w  = _n_comp(&nop, sp_w, cap_w, tel, los_o, tel_o);
      // SBIP and SBIN get sized during assembly
      if ( nop_w > 0 ) {
        ++yep_w; _n_emit(&yep, u3nc(SBIP, nop_w));
      }
      ++tot_w; _n_emit(ops, u3nc(SBIN, yep_w));
      tot_w += yep_w; _n_apen(ops, yep);
      tot_w += nop_w; _n_apen(ops, nop);
      break;
    }

    case 7:
      u3x_cell(arg, &hed, &tel);
      tot_w += _n_comp(ops, sp_w, cap_w, hed, los_o, c3n);
      tot_w += _n_comp(ops, sp_w, cap_w, tel, c3y, tel_o);
      break;

    case 8:
      u3x_cell(arg, &hed, &tel);
      tot_w += _n_comp(ops, sp_w, cap_w, hed, c3n, c3n);
      ++tot_w; _n_emit(ops, (c3y == los_o) ? SNOL : SNOC);
      if ( c3y == los_o ) {
        --*sp_w;
      }
      tot_w += _n_comp(ops, sp_w, cap_w, tel, c3y, tel_o);
      break;

    case 9:
      u3x_cell(arg, &hed, &tel);
      if ( 3 == u3qc_cap(hed) ) {
        u3_noun mac = u3nq(7, u3k(tel), 2, u3nt(u3nc(0, 1), 0, u3k(hed)));
        tot_w += _n_comp(ops, sp_w, cap_w, mac, los_o, tel_o);
        u3z(mac);
      }
      else {
        c3_o lis_o = (c3y == tel_o) ? c3y : los_o;
        tot_w += _n_comp(ops, sp_w, cap_w, tel, lis_o, c3n);
        op_y = (c3y == tel_o) ? TICB : KICB; // overflows to TICS/KICS
        ++tot_w; _n_emit(ops, u3nc(op_y, u3k(hed)));
      }
      break;

    case 10:
      u3x_cell(arg, &hed, &tel);
      tot_w += _n_bint(ops, sp_w, cap_w, hed, tel, los_o, tel_o);
      break;

    case 11:
      u3x_cell(arg, &hed, &tel);
      tot_w += _n_comp(ops, sp_w, cap_w, hed, c3n, c3n);
      ++tot_w; _n_emit(ops, SWAP);
      tot_w += _n_comp(ops, sp_w, cap_w, tel, c3n, c3n);
      ++tot_w; _n_emit(ops, (c3y == los_o) ? WILS : WISH);
      *sp_w -= ( c3y == los_o ) ? 2 : 1;
      break;

    case 12: {
      u3_noun axe, nef;
      u3x_cell(arg, &hed, &tel);
      u3x_cell(hed, &axe, &nef);
      tot_w += _n_comp(ops, sp_w, cap_w, tel, c3n, c3n);
      ++tot_w; _n_emit(ops, SWAP);
      tot_w += _n_comp(ops, sp_w, cap_w, nef, c3n, c3n);

      ++tot_w;
      switch ( axe ) {
        case 2:
          _n_emit(ops, (c3y == los_o) ? MUTH : KUTH);
          break;

        case 3:
          _n_emit(ops, (c3y == los_o) ? MUTT : KUTT);
          break;

        case u3x_sam:
          _n_emit(ops, (c3y == los_o) ? MUSM : KUSM);
          break;

        default:
          op_y = (c3y == los_o)
               ? (axe <= 0xFF) ? MUTB : (axe <= 0xFFFF) ? MUTS : MITB  // overflows to MITS
               : (axe <= 0xFF) ? KUTB : (axe <= 0xFFFF) ? KUTS : KITB; // overflows to KITS
          _n_emit(ops, u3nc(op_y, u3k(axe)));
          break;
      }
      *sp_w -= ( c3y == los_o ) ? 2 : 1;
      break;
    }

    default:
      u3m_bail(c3__exit);
      return 0;
  }
#ifdef U3_CPU_DEBUG
  c3_assert(*sp_w > ((c3y == los_o) ? 0 : 1));
#endif
  return tot_w;
}

/* _n_resh(): read a c3_s from the bytecode stream
 */
static inline c3_s
_n_resh(c3_y* buf, c3_w* ip_w)
{
  c3_y les = buf[(*ip_w)++];
  c3_y mos = buf[(*ip_w)++];
  return les | (mos << 8);
}

/* _n_rewo(): read a c3_w from the bytecode stream.
 */
static inline c3_w
_n_rewo(c3_y* buf, c3_w* ip_w)
{
  c3_y one = buf[(*ip_w)++],
       two = buf[(*ip_w)++],
       tre = buf[(*ip_w)++],
       qua = buf[(*ip_w)++];
  return one | (two << 8) | (tre << 16) | (qua << 24);
}

#ifdef VERBOSE_BYTECODE
/* _n_print_byc(): print bytecode. used for debugging.
 */
static void
_n_print_byc(c3_y* pog, c3_w her_w)
{
  c3_w ip_w = 0;
  if ( her_w == 0 ) {
    fprintf(stderr, "begin: {");
  }
  else {
    fprintf(stderr, "[%d]resume: {", her_w);
  }
  int first = 1;
  while ( pog[ip_w] ) {
    fprintf(stderr, "[%d]", ip_w);
    if ( first ) {
      first = 0;
    }
    else if (ip_w == her_w) {
      fprintf(stderr, " [*]");
    }
    else {
      fprintf(stderr, " ");
    }
    switch ( _n_arg(pog[ip_w]) ) {
      case 0:
        fprintf(stderr, "%s", opcode_names[pog[ip_w++]]);
        break;

      case 1:
        fprintf(stderr, "[%s ", opcode_names[pog[ip_w++]]);
        fprintf(stderr, "%u]", pog[ip_w++]);
        break;

      case 2:
        fprintf(stderr, "[%s ", opcode_names[pog[ip_w++]]);
        fprintf(stderr, "%u]", _n_resh(pog, &ip_w));
        break;

      case 4:
        fprintf(stderr, "[%s", opcode_names[pog[ip_w++]]);
        fprintf(stderr, "%u]", _n_rewo(pog, &ip_w));
        break;
      default:
        c3_assert(0);
        break;
    }
  }
  fprintf(stderr, "[%d] halt}\r\n", ip_w);
}
#endif

/* _n_bite(): compile a nock formula to bytecode. RETAIN.
 */
static inline u3n_prog*
_n_bite(u3_noun fol) {
  c3_w sp_w    = 1,
       cap_w   = 1;
  u3_noun ops  = u3_nul;
  _n_comp(&ops, &sp_w, &cap_w, fol, c3y, c3y);
  u3n_prog* pog_u = _n_prog_from_ops(ops, cap_w);
  return pog_u;
}

/* _n_find(): return prog for given formula with prefix (u3_nul for none).
 *            RETAIN.
 */
static u3n_prog*
_n_find(u3_noun pre, u3_noun fol)
{
  u3_noun key = u3nc(u3k(pre), u3k(fol));
  u3_weak pog = u3h_git(u3R->byc.har_p, key);
  if ( u3_none != pog ) {
    u3z(key);
    return u3to(u3n_prog, pog);
  }
  else if ( u3R != &u3H->rod_u ) {
    u3a_road* rod_u = u3R;
    while ( rod_u->par_p ) {
      rod_u = u3to(u3a_road, rod_u->par_p);
      pog   = u3h_git(rod_u->byc.har_p, key);
      if ( u3_none != pog ) {
        c3_w i_w;
        u3n_prog* old = _n_prog_old(u3to(u3n_prog, pog)); 
        for ( i_w = 0; i_w < old->reg_u.len_w; ++i_w ) {
          u3j_rite* rit_u = &(old->reg_u.rit_u[i_w]);
          rit_u->own_o = c3n;
        }
        for ( i_w = 0; i_w < old->cal_u.len_w; ++i_w ) {
          u3j_site* sit_u = &(old->cal_u.sit_u[i_w]);
          sit_u->bat   = u3_none;
          sit_u->pog_p = 0;
          sit_u->fon_o = c3n;
        }
        u3h_put(u3R->byc.har_p, key, u3a_outa(old));
        u3z(key);
        return old;
      }
    }
  }

  {
    u3n_prog* gop = _n_bite(fol);
    u3h_put(u3R->byc.har_p, key, u3a_outa(gop));
    u3z(key);
    return gop;
  }
}

/* u3n_find(): return prog for given formula,
 *             split by key (u3_nul for no key). RETAIN.
 */
u3p(u3n_prog)
u3n_find(u3_noun key, u3_noun fol)
{
  u3p(u3n_prog) pog_p;
  u3t_on(noc_o);
  pog_p = u3of(u3n_prog, _n_find(key, fol));
  u3t_off(noc_o);
  return pog_p;
}

/* _n_kick(): stop tracing noc and kick a u3j_site.
 */
static u3_weak
_n_kick(u3_noun cor, u3j_site* sit_u)
{
  u3_weak pro;
  u3t_off(noc_o);
  pro = u3j_site_kick(cor, sit_u);
  u3t_on(noc_o);
  return pro;
}

/* _n_kale(): bail(exit) if not cell
 */
static inline u3_noun
_n_kale(u3_noun a)
{
  if ( c3n == u3du(a) ) {
    u3m_bail(c3__exit);
  }
  return a;
}

typedef struct _bf {
  struct _bf* pre_u;   // previous frame
  u3n_prog*   pog_u;   // program
  c3_w        ip_w;    // instruction pointer
  c3_w        sp_w;    // stack pointer
  u3_noun     tak[0];  // local stack space
} burnframe;

static burnframe*
_n_push_frame(burnframe* pre_u, u3n_prog* pog_u, c3_o nor_o)
{
  burnframe* fam_u;
  c3_w       len_w = c3_wiseof(burnframe) + pog_u->cap_w;

  if ( c3y == nor_o ) {
    u3R->cap_p -= len_w;
    fam_u = u3to(burnframe, u3R->cap_p);
  }
  else {
    fam_u = u3to(burnframe, u3R->cap_p);
    u3R->cap_p += len_w;
  }

  fam_u->pre_u = pre_u;
  fam_u->pog_u = pog_u;
  fam_u->ip_w  = 0;
  fam_u->sp_w  = 0;

  return fam_u;
}

static burnframe*
_n_pop_frame(burnframe *fam_u, c3_o nor_o)
{
  c3_w len_w       = c3_wiseof(burnframe) + fam_u->pog_u->cap_w;
  burnframe *pre_u = fam_u->pre_u;

  if ( c3y == nor_o ) {
    u3R->cap_p += len_w;
  }
  else {
    u3R->cap_p -= len_w;
  }

  return pre_u;
}

/* _n_burn(): pog: program
 *            bus: subject (TRANSFER)
 */
static u3_noun
_n_burn(u3n_prog* pog_u, u3_noun bus)
{
  /* OPCODE TABLE */
  static void* lab[] = {
    &&do_halt, &&do_bail,
    &&do_copy, &&do_swap, &&do_toss,
    &&do_auto, &&do_ault, &&do_snoc, &&do_snol,
    &&do_head, &&do_held, &&do_tail, &&do_tall,
    &&do_fabk, &&do_fask, &&do_fibk, &&do_fisk,
    &&do_fabl, &&do_fasl, &&do_fibl, &&do_fisl,
    &&do_lit0, &&do_lit1, &&do_litb, &&do_lits,
    &&do_libk, &&do_lisk,
    &&do_lil0, &&do_lil1, &&do_lilb, &&do_lils,
    &&do_libl, &&do_lisl,
    &&do_nolk, &&do_noct, &&do_nock,
    &&do_deep, &&do_bump,
    &&do_sam0, &&do_sam1, &&do_samb, &&do_sams,
    &&do_sanb, &&do_sans,
    &&do_same, &&do_salm, &&do_samc,
    &&do_sbip, &&do_sips, &&do_swip,
    &&do_sbin, &&do_sins, &&do_swin,
    &&do_kicb, &&do_kics, &&do_ticb, &&do_tics,
    &&do_wils, &&do_wish,
    &&do_bush, &&do_sush,
    &&do_drop, &&do_heck, &&do_slog,
    &&do_bast, &&do_sast,
    &&do_balt, &&do_salt,
    &&do_skib, &&do_skis, &&do_slib, &&do_slis,
    &&do_save,
    &&do_muth, &&do_kuth, &&do_mutt, &&do_kutt,
    &&do_musm, &&do_kusm,
    &&do_mutb, &&do_muts, &&do_mitb, &&do_mits,
    &&do_kutb, &&do_kuts, &&do_kitb, &&do_kits,
  };

  u3j_site* sit_u;
  u3j_rite* rit_u;
  u3n_memo* mem_u;
  u3n_prog* gop_u; 
  c3_y *pog = pog_u->byc_u.ops_y;
  c3_w sip_w, sp_w = 0, ip_w = 0;
  c3_o nor_o = u3a_is_north(u3R);
  u3_noun tmp, x, o;

#ifdef VERBOSE_BYTECODE
  u3n_prog* ori_u = pog_u;
  fprintf(stderr, "top call: %p (cap_p: %d) (%s)\r\n", ori_u, u3R->cap_p, c3y == nor_o ? "north" : "south");
#endif
  burnframe* fam   = _n_push_frame(NULL, pog_u, nor_o);
  u3_noun* tak     = fam->tak;

#define BURN_SWAP()     tmp = tak[sp_w-1]; tak[sp_w-1] = tak[sp_w]; tak[sp_w] = tmp
#define BURN_PUSH(som)  tak[++sp_w] = som;
#define BURN_POP()      tak[sp_w--]
#define BURN_TOP        tak[sp_w]
#define BURN_TOSS()     u3z(BURN_POP())
#define BURN_REP(som)   u3z(BURN_TOP); BURN_TOP = som

  BURN_TOP = bus;

#ifdef U3_CPU_DEBUG
  u3R->pro.nox_d += 1;
#endif
#ifdef VERBOSE_BYTECODE
  #define BURN() fprintf(stderr, "[%d]%s ", sp_w, opcode_names[pog[ip_w]]); BURN_CHK(); goto *lab[pog[ip_w++]]
#else
  #define BURN() BURN_CHK(); goto *lab[pog[ip_w++]]
#endif
  BURN();
  {
    do_halt: // [product ...burnframes...]
#ifdef U3_CPU_DEBUG
      c3_assert( 0 == sp_w );
#endif
      x   = *tak;
      fam = _n_pop_frame(fam, nor_o);
      if ( NULL == fam ) {
#ifdef VERBOSE_BYTECODE
        fprintf(stderr, "top return: %p (cap_p: %d)\r\n", ori_u, u3R->cap_p);
#endif
        return x;
      }
      else {
#ifdef VERBOSE_BYTECODE
        fprintf(stderr, "local return\r\n");
#endif
        pog_u = fam->pog_u;
        pog   = pog_u->byc_u.ops_y;
        ip_w  = fam->ip_w;
        sp_w  = fam->sp_w;
        tak   = fam->tak;
        BURN_PUSH(x);

#ifdef VERBOSE_BYTECODE
        _n_print_byc(pog, ip_w);
#endif
        BURN();
      }

    do_bail:
      u3m_bail(c3__exit);
      return u3_none;

    do_copy:
      o = u3k(BURN_TOP);
      BURN_PUSH(o);
      BURN();

    do_swap:
      BURN_SWAP();
      BURN();

    do_toss:
      BURN_CHK();
      BURN_TOSS();
      BURN();

    do_auto:                         // [tel bus hed]
      BURN_CHK();
      x = BURN_POP();                // [bus hed]
      BURN_SWAP();                   // [hed bus]
      BURN_TOP = u3nc(BURN_TOP, x);  // [pro bus]
      BURN();

    do_ault:                         // [tel bus hed]
      BURN_CHK();
      x = BURN_POP();                // [bus hed]
      BURN_CHK();
      BURN_TOSS();                   // [hed]
      BURN_TOP = u3nc(BURN_TOP, x);  // [pro]
      BURN();
    
    do_snoc: // [hed tel]
      BURN_CHK();
      x = BURN_POP();
      o = u3nc(x, u3k(BURN_TOP));
      BURN_PUSH(o);
      BURN();

    do_snol:
      x = BURN_POP();
      BURN_CHK();
      BURN_TOP = u3nc(x, BURN_TOP);
      BURN();

    do_head:
      x = u3k(u3h(_n_kale(BURN_TOP)));
      BURN_PUSH(x);
      BURN();

    do_held:
      x = u3k(u3h(_n_kale(BURN_TOP)));
      BURN_REP(x);
      BURN();

    do_tail:
      x = u3k(u3t(_n_kale(BURN_TOP)));
      BURN_PUSH(x);
      BURN();

    do_tall:
      x = u3k(u3t(_n_kale(BURN_TOP)));
      BURN_REP(x);
      BURN();

    do_fisk:
      x = pog_u->lit_u.non[_n_resh(pog, &ip_w)];
      goto frag_in;

    do_fibk:
      x = pog_u->lit_u.non[pog[ip_w++]];
      goto frag_in;

    do_fask:
      x = _n_resh(pog, &ip_w);
      goto frag_in;

    do_fabk:
      x = pog[ip_w++];
    frag_in:
      o = u3k(u3x_at(x, BURN_TOP));
      BURN_PUSH(o);
      BURN();

    do_fisl:
      x = pog_u->lit_u.non[_n_resh(pog, &ip_w)];
      goto flag_in;

    do_fibl:
      x = pog_u->lit_u.non[pog[ip_w++]];
      goto flag_in;

    do_fasl:
      x = _n_resh(pog, &ip_w);
      goto flag_in;

    do_fabl:
      x = pog[ip_w++];
    flag_in:
      o = u3k(u3x_at(x, BURN_TOP));
      BURN_REP(o);
      BURN();

    do_lit0:
      BURN_PUSH(0);
      BURN();

    do_lit1:
      BURN_PUSH(1);
      BURN();

    do_litb:
      BURN_PUSH(pog[ip_w++]);
      BURN();

    do_lits:
      BURN_PUSH(_n_resh(pog, &ip_w));
      BURN();

    do_libk:
      BURN_PUSH(u3k(pog_u->lit_u.non[pog[ip_w++]]));
      BURN();

    do_lisk:
      BURN_PUSH(u3k(pog_u->lit_u.non[_n_resh(pog, &ip_w)]));
      BURN();

    do_lil1:
      x = 1;
      goto lil_in;

    do_lilb:
      x = pog[ip_w++];
      goto lil_in;

    do_lils:
      x = _n_resh(pog, &ip_w);
      goto lil_in;

    do_libl:
      x = u3k(pog_u->lit_u.non[pog[ip_w++]]);
      goto lil_in;

    do_lisl:
      x = u3k(pog_u->lit_u.non[_n_resh(pog, &ip_w)]);
      goto lil_in;

    do_lil0:
      x = 0;
    lil_in:
      BURN_REP(x);
      BURN();

    do_noct:                // [fol old bus]
      o   = BURN_POP();     // [old bus]
      BURN_TOSS();          // [bus]
      x   = BURN_POP();     // empty
      fam = _n_pop_frame(fam, nor_o);

#ifdef VERBOSE_BYTECODE
      fprintf(stderr, "\r\ntail nock: %u\r\n", o);
#endif
      goto nock_out;

    do_nolk:                // [fol old bus]
      o = BURN_POP();       // [old bus]
      BURN_TOSS();          // [bus]
      goto nock_in;

    do_nock:                // [fol old bus]
      o = BURN_POP();       // [old bus]
      BURN_SWAP();          // [bus old]
    nock_in:
      x = BURN_POP();
      fam->ip_w = ip_w;
      fam->sp_w = sp_w;
#ifdef VERBOSE_BYTECODE
      fprintf(stderr, "\r\nhead nock: %u", o);
#endif
    nock_out:
      gop_u = _n_find(u3_nul, o);
      fam   = _n_push_frame(fam, gop_u, nor_o);
      pog_u = gop_u;
      pog   = pog_u->byc_u.ops_y;
      tak   = fam->tak;
      ip_w  = sp_w = 0;
      *tak  = x;
#ifdef U3_CPU_DEBUG
    u3R->pro.nox_d += 1;
#endif
#ifdef VERBOSE_BYTECODE
      _n_print(o, c3n);
      _n_print_byc(pog, ip_w);
#endif
      u3z(o);
      BURN();

    do_deep:
      x = u3du(BURN_TOP);
      BURN_REP(x);
      BURN();

    do_bump:
      BURN_TOP = u3i_vint(BURN_TOP);
      BURN();

    do_sam0:
      if ( BURN_TOP != 0 ) {
        BURN_REP(c3n);
      }
      BURN();

    do_sam1:
      if ( BURN_TOP == 1 ) {
        BURN_TOP = c3y;
      }
      else {
        BURN_REP(c3n);
      }
      BURN();

    do_samb:
      if ( BURN_TOP == pog[ip_w++] ) {
        BURN_TOP = c3y;
      }
      else {
        BURN_REP(c3n);
      }
      BURN();

    do_sams:
      if ( BURN_TOP == _n_resh(pog, &ip_w) ) {
        BURN_TOP = c3y;
      }
      else {
        BURN_REP(c3n);
      }
      BURN();

    do_sans:
      x = pog_u->lit_u.non[_n_resh(pog, &ip_w)];
      goto samn_in;
    do_sanb:
      x = pog_u->lit_u.non[pog[ip_w++]];
    samn_in:
      o = u3r_sing(x, BURN_TOP);
      BURN_REP(o);
      BURN();

    do_salm:
      x = BURN_POP();
      BURN_TOSS();
      goto same_in;

    do_same:
      x = BURN_POP();
      BURN_SWAP();
    same_in:
      o = u3r_sing(x, BURN_TOP);
      u3z(x);
      BURN_REP(o);
      BURN();

    do_samc:
      x = BURN_TOP;
      BURN_TOP = u3r_sing(u3h(x), u3t(x));
      u3z(x);
      BURN();

    do_sbip:
      sip_w = pog[ip_w++];
      ip_w += sip_w;
      BURN();

    do_sips:
      sip_w = _n_resh(pog, &ip_w);
      ip_w += sip_w;
      BURN();

    do_swip:
      sip_w = _n_rewo(pog, &ip_w);
      ip_w += sip_w;
      BURN();

    do_swin:
      sip_w = _n_rewo(pog, &ip_w);
      goto skin_in;

    do_sins:
      sip_w = _n_resh(pog, &ip_w);
      goto skin_in;

    do_sbin:
      sip_w = pog[ip_w++];
    skin_in:
      x = BURN_POP();
      if ( c3n == x ) {
        ip_w += sip_w;
      }
      else if ( c3y != x ) {
        u3m_bail(c3__exit);
        return u3_none;
      }
      BURN();

    do_kics:
      x = _n_resh(pog, &ip_w);
      goto kick_in;

    do_kicb:
      x = pog[ip_w++];
    kick_in:
      sit_u    = &(pog_u->cal_u.sit_u[x]);
      o        = BURN_TOP;
      BURN_TOP = _n_kick(o, sit_u);
      if ( u3_none == BURN_TOP ) {
        fam->sp_w = sp_w - 1;
        fam->ip_w = ip_w;
        gop_u     = u3to(u3n_prog, sit_u->pog_p);
        fam       = _n_push_frame(fam, gop_u, nor_o);
        pog_u     = gop_u;
        pog       = pog_u->byc_u.ops_y;
        tak       = fam->tak;
        ip_w      = sp_w = 0;
        *tak      = o;
#ifdef VERBOSE_BYTECODE
        fprintf(stderr, "\r\nhead kick: %u, sp: %d\r\n", u3r_at(sit_u->axe, o), sp_w);
        _n_print(u3r_at(sit_u->axe, o), c3n);
        _n_print_byc(pog, ip_w);
#endif
#ifdef U3_CPU_DEBUG
    u3R->pro.nox_d += 1;
#endif
      }
#ifdef VERBOSE_BYTECODE
      else {
        fprintf(stderr, "\r\nhead jet (return to %p)\r\n", ori_u);
        _n_print_byc(pog, ip_w);
      }
#endif
      BURN();

    do_tics:
      x = _n_resh(pog, &ip_w);
      goto tick_in;

    do_ticb:
      x = pog[ip_w++];
    tick_in:
      sit_u    = &(pog_u->cal_u.sit_u[x]);
      o        = BURN_TOP;
      BURN_TOP = _n_kick(o, sit_u);
      if ( u3_none == BURN_TOP ) {
        gop_u = u3to(u3n_prog, sit_u->pog_p);
        if ( pog_u != gop_u ) {
          if ( pog_u->cap_w == gop_u->cap_w ) {
            // reuse frame
            fam->pog_u = gop_u;
          }
          else {
            // replace frame
            fam = _n_pop_frame(fam, nor_o);
            fam = _n_push_frame(fam, gop_u, nor_o);
            tak = fam->tak;
          }
          pog_u = gop_u;
          pog   = pog_u->byc_u.ops_y;
        }
        ip_w = sp_w = 0;
        *tak = o;
#ifdef VERBOSE_BYTECODE
        fprintf(stderr, "\r\ntail kick: %u, sp: %d\r\n", u3x_at(sit_u->axe, o), sp_w);
        _n_print_byc(pog, ip_w);
#endif
#ifdef U3_CPU_DEBUG
    u3R->pro.nox_d += 1;
#endif
      }
#ifdef VERBOSE_BYTECODE
      else {
        fprintf(stderr, "tail jet\r\n");
      }
#endif
      BURN();

    do_wils:                   // [gof bus ref]
      o = BURN_POP();          // [bus ref]
      BURN_TOSS();             // [ref]
      goto wish_in;

    do_wish:                   // [gof bus ref]
      o = BURN_POP();          // [bus ref]
      BURN_SWAP();             // [ref bus]
    wish_in:
      u3t_off(noc_o);
      x = u3m_soft_esc(BURN_TOP, u3k(o));
      u3t_on(noc_o);

      if ( c3n == u3du(x) ) {
        u3m_bail(u3nt(1, o, 0));
        return u3_none;
      }
      else if ( c3n == u3du(u3t(x)) ) {
        //  replace with proper error stack push
        u3t_push(u3nc(c3__hunk, _n_mush(o)));
        u3m_bail(c3__exit);
        return u3_none;
      }
      else {
        u3z(o);
        BURN_TOP = u3k(u3t(u3t(x)));
        u3z(x);
      }
      BURN();

    do_sush:
      x = _n_resh(pog, &ip_w);
      goto cush_in;

    do_bush:
      x = pog[ip_w++];
    cush_in:
      x = u3k(pog_u->lit_u.non[x]);
      o = BURN_POP();
      u3t_push(u3nc(x, o));
      BURN();

    do_drop:
      u3t_drop();
      BURN();

    do_heck:
      x = BURN_POP();
      if ( c3y == u3ud(x) ) {
        u3t_off(noc_o);
        u3t_heck(x);
        u3t_on(noc_o);
      }
      else {
        u3z(x);
      }
      BURN();

    do_slog:
      x = BURN_POP();
      if ( !(u3C.wag_w & u3o_quiet) ) {
        u3t_off(noc_o);
        u3t_slog(x);
        u3t_on(noc_o);
      }
      else {
        u3z(x);
      }
      BURN();

    do_sast:
      x   = _n_resh(pog, &ip_w);
      goto fast_in;

    do_bast:
      x   = pog[ip_w++];
      goto fast_in;

    do_salt:
      x   = _n_resh(pog, &ip_w);
      goto falt_in;
    do_balt:
      x   = pog[ip_w++];
    falt_in:                   // [pro bus clu]
      o   = BURN_POP();        // [bus clu]
      BURN_TOSS();             // [clu]
      goto fast_out;

    fast_in:                   // [pro bus clu]
      o   = BURN_POP();        // [bus clu]
      BURN_SWAP();             // [clu bus]
    fast_out:
      rit_u = &(pog_u->reg_u.rit_u[x]);
      u3t_off(noc_o);
      u3j_rite_mine(rit_u, BURN_TOP, u3k(o));
      u3t_on(noc_o);
      BURN_TOP = o;
      BURN();

    do_skis:
      x     = _n_resh(pog, &ip_w);
      goto skim_in;

    do_skib:
      x     = pog[ip_w++];
    skim_in:
      mem_u = &(pog_u->mem_u.sot_u[x]);
      x     = u3k(BURN_TOP);
      goto skim_out;

    do_slis:
      x     = _n_resh(pog, &ip_w);
      goto slim_in;

    do_slib:
      x     = pog[ip_w++];
    slim_in:
      mem_u = &(pog_u->mem_u.sot_u[x]);
      x     = BURN_POP();
    skim_out:
      o = u3k(mem_u->key);
      x = u3nc(x, o);
      o = u3z_find(144 + c3__nock, x);
      if ( u3_none == o ) {
        BURN_PUSH(x);
        BURN_PUSH(u3k(u3h(x)));
      }
      else {
        ip_w += mem_u->sip_l;
        BURN_PUSH(o);
        u3z(x);
      }
      BURN();

    do_save:
      x = BURN_POP();
      if ( &(u3H->rod_u) != u3R ) {
        u3z_save(144 + c3__nock, BURN_TOP, x);
      }
      BURN_REP(x);
      BURN();

    do_kuth:
      o = BURN_POP();
      BURN_SWAP();
      goto muth_in;

    do_muth:
      o = BURN_POP();
      BURN_TOSS();
    muth_in:
      x = 2;
      goto edit_in;

    do_kutt:
      o = BURN_POP();
      BURN_SWAP();
      goto mutt_in;

    do_mutt:
      o = BURN_POP();
      BURN_TOSS();
    mutt_in:
      x = 3;
      goto edit_in;

    do_kusm:
      o = BURN_POP();
      BURN_SWAP();
      goto musm_in;

    do_musm:
      o = BURN_POP();
      BURN_TOSS();
    musm_in:
      x = 6;
      goto edit_in;

    do_kitb:
      x = pog_u->lit_u.non[pog[ip_w++]];
      goto kut_in;

    do_kits:
      x = pog_u->lit_u.non[_n_resh(pog, &ip_w)];
      goto kut_in;

    do_kuts:
      x = _n_resh(pog, &ip_w);
      goto kut_in;

    do_kutb:
      x = pog[ip_w++];
    kut_in:
      o = BURN_POP();
      BURN_SWAP();
      goto edit_in;

    do_mitb:
      x = pog_u->lit_u.non[pog[ip_w++]];
      goto mut_in;

    do_mits:
      x = pog_u->lit_u.non[_n_resh(pog, &ip_w)];
      goto mut_in;

    do_muts:
      x = _n_resh(pog, &ip_w);
      goto mut_in;

    do_mutb:
      x = pog[ip_w++];
    mut_in:
      o = BURN_POP();
      BURN_TOSS();
    edit_in:
      BURN_TOP = u3i_edit(BURN_TOP, x, o);
      BURN();
  }
}

/* _n_burn_out(): execute u3n_prog with bus as subject.
static u3_noun
_n_burn_out(u3_noun bus, u3n_prog* pog_u)
{
  c3_ys mov, off;
  if ( c3y == u3a_is_north(u3R) ) {
    mov = -1;
    off = 0;
  }
  else {
    mov = 1;
    off = -1;
  }
  return _n_burn(pog_u, bus, mov, off);
}
*/

/* u3n_burn(): execute u3n_prog with bus as subject.
 */
u3_noun
u3n_burn(u3p(u3n_prog) pog_p, u3_noun bus)
{
  u3_noun pro;
  u3t_on(noc_o);
  pro = _n_burn(u3to(u3n_prog, pog_p), bus);
  u3t_off(noc_o);
  return pro;
}

/* _n_burn_on(): produce .*(bus fol) with bytecode interpreter
 */
static u3_noun
_n_burn_on(u3_noun bus, u3_noun fol)
{
  u3n_prog* pog_u = _n_find(u3_nul, fol);

  u3z(fol);
  return _n_burn(pog_u, bus);
}

/* u3n_nock_on(): produce .*(bus fol).  Do not virtualize.
*/
u3_noun
u3n_nock_on(u3_noun bus, u3_noun fol)
{
  u3_noun pro;

  u3t_on(noc_o);
#if 0
  pro = _n_nock_on(bus, fol);
#else
  pro = _n_burn_on(bus, fol);
#endif
  u3t_off(noc_o);

  return pro;
}

/* _n_prog_take_dat(): copy references from src u3n_prog. overwritten
 *                     values in dst u3n_prog are lost/freed only if
 *                     los_o is yes.
 */
static void
_n_prog_take_dat(u3n_prog* dst_u, u3n_prog* src_u, c3_o los_o)
{
  c3_w i_w;
  for ( i_w = 0; i_w < src_u->lit_u.len_w; ++i_w ) {
    u3_noun* dst = &(dst_u->lit_u.non[i_w]);
    u3_noun* src = &(src_u->lit_u.non[i_w]);
    u3_noun  old = *dst;
    *dst = u3a_take(*src);
    if ( c3y == los_o ) {
      u3z(old);
    }
  }

  for ( i_w = 0; i_w < src_u->mem_u.len_w; ++i_w ) {
    u3n_memo* dst = &(dst_u->mem_u.sot_u[i_w]);
    u3n_memo* src = &(src_u->mem_u.sot_u[i_w]);
    u3_noun  old = dst->key;
    dst->sip_l   = src->sip_l;
    dst->key     = u3a_take(src->key);
    if ( c3y == los_o ) {
      u3z(old);
    }
  }

  for ( i_w = 0; i_w < src_u->cal_u.len_w; ++i_w ) {
    u3j_site_copy(&(dst_u->cal_u.sit_u[i_w]),
                  &(src_u->cal_u.sit_u[i_w]), los_o);
  }

  for ( i_w = 0; i_w < src_u->reg_u.len_w; ++i_w ) {
    u3j_rite_copy(&(dst_u->reg_u.rit_u[i_w]),
                  &(src_u->reg_u.rit_u[i_w]), los_o);
  }
}

/* _n_prog_take(): copy program from a junior road
 */
static u3n_prog*
_n_prog_take(u3n_prog* pog_u)
{
  u3n_prog* gop_u;

  if ( c3y == pog_u->byc_u.own_o ) {
    gop_u = _n_prog_new(pog_u->byc_u.len_w,
        pog_u->cal_u.len_w, pog_u->reg_u.len_w,
        pog_u->lit_u.len_w, pog_u->mem_u.len_w);
    gop_u->cap_w = pog_u->cap_w;
    memcpy(gop_u->byc_u.ops_y, pog_u->byc_u.ops_y, pog_u->byc_u.len_w);
  }
  else {
    gop_u = _n_prog_old(pog_u);
  }
  _n_prog_take_dat(gop_u, pog_u, c3n);

  return gop_u;
}


/* _n_prog_free(): free memory retained by program
*/
static void
_n_prog_free(u3n_prog* pog_u)
{
  c3_w i_w;

  for ( i_w = 0; i_w < pog_u->lit_u.len_w; ++i_w ) {
    u3z(pog_u->lit_u.non[i_w]);
  }

  for ( i_w = 0; i_w < pog_u->mem_u.len_w; ++i_w ) {
    u3z(pog_u->mem_u.sot_u[i_w].key);
  }

  for ( i_w = 0; i_w < pog_u->cal_u.len_w; ++i_w ) {
    u3j_site_lose(&(pog_u->cal_u.sit_u[i_w]));
  }

  for ( i_w = 0; i_w < pog_u->reg_u.len_w; ++i_w ) {
    u3j_rite_lose(&(pog_u->reg_u.rit_u[i_w]));
  }

  u3a_free(pog_u);
}

/* _n_reap(): reap key and value from byc table.
*/
static void
_n_reap(u3_noun kev)
{
  u3_noun fol = u3h(kev);
  u3_noun got = u3t(kev);
  u3_noun lof = u3a_take(fol);
  u3_noun tog;
  u3_weak con = u3h_get(u3R->byc.har_p, lof);
  u3n_prog* pog_u = u3to(u3n_prog, got);
  
  if ( u3_none == con ) {
    tog = u3a_outa(_n_prog_take(pog_u));
    u3h_put(u3R->byc.har_p, lof, tog);
  }
  else {
    u3n_prog* sep_u = u3to(u3n_prog, con);
    _n_prog_take_dat(sep_u, pog_u, c3y);
    tog = u3a_outa(sep_u);
  }
  u3z(lof);
}

/* u3n_reap(): promote bytecode state.
*/
void
u3n_reap(u3p(u3h_root) har_p)
{
  u3h_walk(har_p, _n_reap);
}

/* _n_ream(): ream program call sites
*/
void
_n_ream(u3_noun kev)
{
  c3_w i_w;
  u3n_prog* pog_u = u3to(u3n_prog, u3t(kev));
  for ( i_w = 0; i_w < pog_u->cal_u.len_w; ++i_w ) {
    u3j_site_ream(&(pog_u->cal_u.sit_u[i_w]));
  }
}

/* u3n_ream(): refresh after restoring from checkpoint.
*/
void
u3n_ream()
{
  c3_assert(u3R == &(u3H->rod_u));
  u3h_walk(u3R->byc.har_p, _n_ream);
}

/* _n_prog_mark(): mark program for gc.
*/
static c3_w
_n_prog_mark(u3n_prog* pog_u)
{
  c3_w i_w, tot_w = u3a_mark_mptr(pog_u);

  for ( i_w = 0; i_w < pog_u->lit_u.len_w; ++i_w ) {
    tot_w += u3a_mark_noun(pog_u->lit_u.non[i_w]);
  }

  for ( i_w = 0; i_w < pog_u->mem_u.len_w; ++i_w ) {
    tot_w += u3a_mark_noun(pog_u->mem_u.sot_u[i_w].key);
  }

  for ( i_w = 0; i_w < pog_u->cal_u.len_w; ++i_w ) {
    tot_w += u3j_site_mark(&(pog_u->cal_u.sit_u[i_w]));
  }

  for ( i_w = 0; i_w < pog_u->reg_u.len_w; ++i_w ) {
    tot_w += u3j_rite_mark(&(pog_u->reg_u.rit_u[i_w]));
  }

  return tot_w;
}

/* _n_bam(): u3h_walk_with helper for u3n_mark
 */
static void
_n_bam(u3_noun kev, void* dat)
{
  c3_w* bam_w  = dat;
  u3n_prog* pog = u3to(u3n_prog, u3t(kev));
  *bam_w += _n_prog_mark(pog);
}

/* u3n_mark(): mark the bytecode cache for gc.
 */
c3_w
u3n_mark()
{
  c3_w bam_w = 0;
  u3p(u3h_root) har_p = u3R->byc.har_p;
  u3h_walk_with(har_p, _n_bam, &bam_w);
  return bam_w + u3h_mark(har_p);
}

/* _n_feb(): u3h_walk helper for u3n_bree
 */
static void
_n_feb(u3_noun kev)
{
  _n_prog_free(u3to(u3n_prog, u3t(kev)));
}

/* u3n_free(): free bytecode cache
 */
void
u3n_free()
{
  u3p(u3h_root) har_p = u3R->byc.har_p;
  u3h_walk(har_p, _n_feb);
  u3h_free(har_p);
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
