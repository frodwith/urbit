!:
:-  %say
|=  *
:-  %noun
=<  %.  :-  42
        =-  ~&  -  -
        =>  to=0
        !.
        !=  =|  i=@
            |-
            =/  up  +(i)
            ?:  =(up to)  i
            $(i up)
    %^  (draw _~)  ~
      ^=  hint
      |=  [bus=* fol=* clu=clue sat=_~]
      sat
    ^=  miss
    |=  [bus=* fol=[op=@ arg=*] sat=_~]
    [~ sat]
=>  |%
    +$  clue
      $@  nam=@
      [nam=@ clu=*]
    --
|%
++  draw
  ::  configurable nock interpreter with state
  |*  state=mold
  =>  |%
      +$  prod
        $:  (unit *)
            sat=state
        ==
      +$  hunt
        $@  ~
        $%  [%& pro=prod]
            [%| con=$-(prod state)]
        ==
      +$  wolf
        $:  $=  hint
            $-  [bus=* fol=* clu=clue sat=state]
              hunt
            $=  miss
            $-  [bus=* fol=[op=@ arg=*] sat=state]
              prod
        ==
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
    ^-  prod
    [~ sat]
  ++  ret
    |=  pro=*
    ^-  prod
    [`pro sat]
  ++  nock
    |=  [bus=* fol=*]
    ::~&  begin=+<
    ::=-  ~&  end=[bus=bus fol=fol pro=-]  -
    ^-  prod
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
      ~!  sub
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
        ^-  prod
        =/  hun  (hint.wol bus +>.fol clu sat)
        ?:  ?=  [%& *]  hun
          pro.hun
        =/  pro  ^$(fol +>.fol)
        ?~  hun  pro
        pro(sat (con.hun pro))
      ?@  +<.fol  (howl +<.fol)
      ?^  +<-.fol  exit
      =^  clu  sat  $(fol +<+.fol)
      ?~  clu  exit
      (howl +<-.fol u.clu)
    ==
  --
--
