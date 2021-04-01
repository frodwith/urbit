!:
:-  %say
|=  *
:-  %noun
=<  =/  scry
      |=  [ref=* pat=*]
      ^-  (unit (unit))
      ``42
    =/  jets  %-  ~(gas by *(map * $-(^ *)))
      :~  :-  /hoon/140/inc
            |=  [bus=* fol=*]
            ~>  %slog.[0 leaf+"omg increment!!"]
            ?^  bus  !!
            +(bus)
      ==
    %-  (road & & & & jets `scry)
    :-  ~
    [12 [1 1] 1 1]
    ::  =>  ..mock
    ::  :-  .
    ::  !.  !=
    ::  =<  (. 9)
    ::  ::  |=  n=@
    ::  ::  !*  n  /hoon/140/dec
    ::  ::  =|  i=@
    ::  ::  |-  ^+  i
    ::  ::  =/  up=@  +(i)
    ::  ::  ?:  =(up n)  i
    ::  ::  $(i up)
    ::  ::  ~>  %jets.~[[4 0 1]^/hoon/140/inc]
    ::  |=  n=@
    ::  ^-  @
    ::  ::  ~>  %toss.=>(n=n ~>(%form./hoon/140/inc +(n)))
    ::  ~+
    ::  ::  ~>  %slog.[0 leaf+"iter"]
    ::  ?:  (lth n 2)  1
    ::  =/  low=@  (dec n)
    ::  %+  add
    ::    $(n low)
    ::  $(n (dec low))
=>  |%
    +$  clue
      $@  nam=@
      [nam=@ clu=*]
    +$  rope
      $:  $%  [%0 pro=*]
              [%1 blk=*]
              [%2 tax=(list [@ *])]
          ==
          pak=(list ^)
      ==
    --
|%
++  road
  |=  $:  mem=?
          log=?
          col=?
          pac=?
          drv=(map * $-(^ *))
          sky=(unit $-(^ (unit (unit))))
      ==
  |=  [bus=* fol=*]
  ^-  rope
  =-  :_  ~(tap by reg)
      ?^  -<   0+u
      ?~  blk  2+tax
      1+u.blk
  %.  +<
  =/  state
    $:  mem=(map ^ (unit *))
        reg=(map * *)
        tax=(list [@ *])
        blk=(unit *)
    ==
  =/  d  (draw state)
  %+  d  *state
  |%
  ++  miss
    |=  [bus=* [op=@ arg=*] sat=state]
    ^-  out.d
    =*  exit  `sat
    ?:  ?|  ?=(~ sky)
            ?=(@ arg)
            !=(12 op)
        ==
      exit
    =/  noc  (d sat ..miss)
    =^  ref  sat  (noc bus -.arg)
    ?~  ref  exit
    =^  pat  sat  (noc bus +.arg)
    ?~  pat  exit
    =/  res  (u.sky u.ref u.pat)
    ?~  res  `sat(blk pat)
    ?~  u.res  `sat(tax [[%hunk u.ref u.pat] tax.sat])
    [u.res sat]
  ++  hunt
    |=  [in.d clu=clue]
    ^-  out.d
    =<  $
    |%
    ++  nock  (d sat ..hunt)
    ++  skip  (nock bus fol)
    ++  $
      ?+  clu  skip
          [?(%hunk %lose %mean %spot) *]
        =/  pro
          =.  tax.sat  [clu tax.sat]
          (nock bus fol)
        ?~  -.pro  pro
        pro(tax tax.sat)
          [%slog *]
        ?.  log  skip
        ~>(%slog.clu.clu skip)
          [%memo *]
        ?.  mem  skip
        =/  key=^  [bus fol]
        =/  got  (~(get by mem.sat) key)
        ?^  got  [u.got sat]
        =/  pro  skip
        pro(mem (~(put by mem.pro) key -.pro))
          [%form *]
        ?.  col  skip
        =/  jet  (~(get by drv) clu.clu)
        =/  pro
          ?~  jet  skip
          ~&  %running-a-jet
          (nock [u.jet bus fol] [9 2 10 [6 0 3] 0 2])
        pro(reg (~(put by reg.pro) fol clu.clu))
          [%jets *]
        ?.  pac  skip
        =/  par=(unit (list ^))  ((soft (list ^)) clu.clu)
        ?~  par  skip
        =.  reg.sat  (~(gas by reg.sat) u.par)
        skip
      ==
    --
  --
++  draw
  ::  configurable nock interpreter with state
  |*  state=mold
  =>  |%
      +$  out   [(unit *) state]
      +$  in    [bus=* fol=* sat=state]
      +$  wolf
        $_  ^?
        |%
        ++  hunt
          =<  $
          $-  [in clu=clue]
          out
        ++  miss
          =<  $
          $-  [bus=* [op=@ arg=*] sat=state]
          out
       --
      ++  frag
        |=  [axe=@ non=*]
        ^-  (unit *)
        ?:  =(0 axe)  ~
        |-  ^-  (unit *)
        ?:  =(1 axe)  `non
        ?@  non  ~
        %=  $
          axe  (mas axe)
          non  ?:  =(2 (cap axe))
                 -.non
               +.non
        ==
      ++  edit
        |=  [axe=@ lit=* big=*]
        ^-  (unit *)
        ?:  =(0 axe)  ~
        |-  ^-  (unit *)
        ?:  =(1 axe)  `lit
        ?@  big  ~
        =/  hed=?  =(2 (cap axe))
        =/  bro  %=  $
                   axe  (mas axe)
                   big  ?:(hed -.big +.big)
                 ==
        ?~  bro  ~
        ?:  hed
          `[u.bro +.big]
        `[-.big u.bro]
      --
  |=  [sat=state wol=wolf]
  =<  nock
  |%
  ++  exit
    ^-  out
    `sat
  ++  ret
    |=  pro=*
    ^-  out
    [`pro sat]
  ++  nock
    |=  [bus=* fol=*]
    ^-  out
    ?@  fol  exit
    ?^  -.fol 
      =^  hed  sat  $(fol -.fol)
      ?~  hed  exit
      =^  tal  sat  $(fol +.fol)
      ?~  tal  exit
      (ret u.hed u.tal)
    ?+  -.fol  (miss.wol bus fol sat)
        %0
      ?^  +.fol  exit
      :_  sat
      (frag +.fol bus)
        %1
      (ret +.fol)
        %2 
      ?@  +.fol  exit
      =^  sub  sat  $(fol +<.fol)
      ?~  sub  exit
      =^  lof  sat  $(fol +>.fol)
      ?~  lof  exit
      $(bus u.sub, fol u.lof)
        %3 
      =^  non  sat  $(fol +.fol)
      ?~  non  exit
      (ret .?(u.non))
        %4
      =^  non  sat  $(fol +.fol)
      ?~  non  exit
      ?^  u.non  exit
      (ret .+(u.non))
        %5
      ?@  +.fol  exit
      =^  a  sat  $(fol +<.fol)
      ?~  a  exit
      =^  b  sat  $(fol +>.fol)
      ?~  b  exit
      (ret .=(u.a u.b))
        %6
      ?@  +.fol  exit
      ?@  +>.fol  exit
      =^  t  sat  $(fol +<.fol)
      ?~  t  exit
      ?+  u.t  exit
        %&  $(fol +>-.fol)
        %|  $(fol +>+.fol)
      ==
        %7
      ?@  +.fol  exit
      =^  sub  sat  $(fol +<.fol)
      ?~  sub  exit
      $(bus u.sub, fol +>.fol)
        %8
      ?@  +.fol  exit
      =^  hed  sat  $(fol +<.fol)
      ?~  hed  exit
      $(bus [u.hed bus], fol +>.fol)
        %9
      ?@  +.fol  exit
      ?^  +<.fol  exit
      =^  cor  sat  $(fol +>.fol)
      ?~  cor  exit
      =/  arm  (frag +<.fol u.cor)
      ?~  arm  exit
      $(bus u.cor, fol u.arm)
        %10
      ?@  +.fol  exit
      ?@  +<.fol  exit
      ?^  +<-.fol  exit
      =^  big  sat  $(fol +>.fol)
      ?~  big  exit
      =^  lit  sat  $(fol +<+.fol)
      ?~  lit  exit
      :_  sat
      (edit +<-.fol u.lit u.big)
        %11
      ?@  +.fol  exit
      =/  howl
        |=  clu=clue
        (hunt.wol [bus +>.fol sat] clu)
      ?@  +<.fol  (howl +<.fol)
      ?^  +<-.fol  exit
      =^  clu  sat  $(fol +<+.fol)
      ?~  clu  exit
      (howl +<-.fol u.clu)
    ==
  --
--
