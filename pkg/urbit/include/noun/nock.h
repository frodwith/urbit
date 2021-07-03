/* i/n/n.h
**
** This file is in the public domain.
*/
  /** Data structures.
  ***
  **/

  /* u3n_memo: %memo hint space
   */
  typedef struct {
    c3_l    sip_l;
    u3_noun key;
  } u3n_memo;

  /* u3n_nemo: %name hint space
   */
  typedef struct {
    u3_noun fol;                      // formula being named
    u3_noun nam;                      // name of formula
    u3_funq dev;                      // native driver
    c3_l    sip_l;                    // number of bytes in unjetted impl
    struct {
      u3_weak bib;                    // book used for authorization
      c3_t    run_t;                  // was [fol nam] in bib?
    } cax_u;                          // authorization cache
  } u3n_nemo;

  /* u3n_adam: %adam hint space
   */
  typedef struct {
    u3_weak bib;                      // cached book input
    u3_weak zoo;                      // cached trap
    u3_weak rob;                      // cached book result
  } u3n_adam;

  /* u3n_prog: program compiled from nock
   */
  typedef struct _u3n_prog {
    struct {
      c3_o      own_o;                // program owns ops_y?
      c3_w      len_w;                // length of bytecode (bytes)
      c3_y*     ops_y;                // actual array of bytes
    } byc_u;                          // bytecode
    struct {
      c3_w      len_w;                // number of literals
      u3_noun*  non;                  // array of literals
    } lit_u;                          // literals
    struct {
      c3_w      len_w;                // number of memo slots
      u3n_memo* sot_u;                // array of memo slots
    } mem_u;                          // memo slot data
    struct {
      c3_w      len_w;                // number of calls sites
      u3j_site* sit_u;                // array of sites
    } cal_u;                          // call site data
    struct {
      c3_w      len_w;                // number of registration sites
      u3j_rite* rit_u;                // array of sites
    } reg_u;                          // registration site data
    struct {
      c3_w      len_w;                // number of name sites
      u3n_nemo* nit_u;                // array of nemos
    } nem_u;                          // name site data
    struct {
      c3_w      len_w;                // number of adam sites
      u3n_adam* mat_u;                // array of adams
    } dam_u;                          // adam site data
  } u3n_prog;

  /**  Functions.
  **/
    /* u3n_nock_on(): produce .*(bus fol).
    */
      u3_noun
      u3n_nock_on(u3_noun bus, u3_noun fol);

    /* u3n_find(): return prog for given formula,
     *             split by key (u3_nul for none). RETAIN.
     */
      u3p(u3n_prog)
      u3n_find(u3_noun key, u3_noun fol);

    /* u3n_burn(): execute u3n_prog with bus as subject.
     */
      u3_noun
      u3n_burn(u3p(u3n_prog) pog_p, u3_noun bus);

    /* u3n_slam_on(): produce (gat sam).
    */
      u3_noun
      u3n_slam_on(u3_noun gat, u3_noun sam);

    /* u3n_kick_on(): fire `gat` without changing the sample.
    */
      u3_noun
      u3n_kick_on(u3_noun gat);

    /* u3n_nock_in(): produce .*(bus fol), as ++toon, in namespace.
    */
      u3_noun
      u3n_nock_in(u3_noun fly, u3_noun bus, u3_noun fol);

    /* u3n_nock_it(): produce .*(bus fol), as ++toon, in namespace.
    */
      u3_noun
      u3n_nock_it(u3_noun sea, u3_noun bus, u3_noun fol);

    /* u3n_nock_et(): produce .*(bus fol), as ++toon, in namespace.
    */
      u3_noun
      u3n_nock_et(u3_noun gul, u3_noun bus, u3_noun fol);

    /* u3n_slam_in(): produce (gat sam), as ++toon, in namespace.
    */
      u3_noun
      u3n_slam_in(u3_noun fly, u3_noun gat, u3_noun sam);

    /* u3n_slam_it(): produce (gat sam), as ++toon, in namespace.
    */
      u3_noun
      u3n_slam_it(u3_noun sea, u3_noun gat, u3_noun sam);

    /* u3n_slam_et(): produce (gat sam), as ++toon, in namespace.
    */
      u3_noun
      u3n_slam_it(u3_noun gul, u3_noun gat, u3_noun sam);

    /* u3n_nock_an(): as slam_in(), but with empty fly.
    */
      u3_noun
      u3n_nock_an(u3_noun bus, u3_noun fol);

    /* u3n_reap(): promote bytecode state.
     */
      void
      u3n_reap(u3p(u3h_root) har_p);

    /* u3n_take(): copy junior bytecode state.
     */
      u3p(u3h_root)
      u3n_take(u3p(u3h_root) har_p);

    /* u3n_mark(): mark bytecode cache.
     */
      c3_w
      u3n_mark(FILE* fil_u);

    /* u3n_reclaim(): clear ad-hoc persistent caches to reclaim memory.
    */
      void
      u3n_reclaim(void);

    /* u3n_rewrite_compact(): rewrite bytecode cache for compaction.
     */
      void
      u3n_rewrite_compact();

    /* u3n_free(): free bytecode cache.
     */
      void
      u3n_free(void);

    /* u3n_ream(): refresh after restoring from checkpoint.
    */
      void
      u3n_ream(void);
