# dir [y x]
Move ← ⊃(
  ∘
| ⨬(⍜(⊡0|-1)
  | ⍜(⊡1|+1)
  | ⍜(⊡0|+1)
  | ⍜(⊡1|-1))
)
Trace        ← ⊃(⊙∘|⋅⍜(⊡|2◌))
TracePartTwo ← ⊃(⊙∘|⍜(⊡|+2◌)⊙::)
Rotate ← (
  ⊃(◌Move|⊙∘)
  ⊃(=1⊡⊙⋅⋅∘|⋅⊙⊙∘)
  ⨬(|◿4+1)
)

CheckBounds ← (
  ⊃(⋅⋅△|⊙⊙∘)
  ⊃(/+≥⊙⋅∘|⋅⊙∘)
  ⊃(/+<0⋅⋅∘|⊙⊙∘)
  +
)

Input            ← &fras "input.txt"
ParseInput       ← ∵(=@#)⊜∘≠@\n.
GetStartPosition ← ⊡0⊚∵(=@^)⊜∘≠@\n.

ParseInput Input
GetStartPosition Input
0

⊃(Trace

  ⍢(Rotate
    Move
    Trace
  | ⊃(◌Move|⊙∘)
    ⊃(⊙⋅⋅◌=0CheckBounds0⊙⋅⋅∘|⋅⊙⊙∘)
  )

  ◌◌
  =2
  /+/+
| ⊃(⇡⋅⋅△|⊙⊙∘)
  /⊂
  ⊃(⋅⊙∘|/⊂⊞(⊂□⊙□)⊙¤⊙⋅⋅∘)
  ⊃(⊙∘|▽⊃(≡(=0≍⊙⋅∘°□⊡0.)|∘):¤⋅∘)
  ⊃(⊙∘|⋅⋅≡(⍜(⊡|1◌)°□⊡0:°□⊡1.))

  ¤{⊙∘}
  ≡(⊂⊙□)
  ≡(⊙⊙(⊡0)⊙°⊂°⊂
    ⊙⊙°□⊙°□°□
  
    ⍢(TracePartTwo
      Rotate
      Rotate
      Move
    | ⊃(⊃(◌Move|⊙∘)
        ⊃(⊙⋅⋅◌=0CheckBounds0⊙⋅⋅∘|⋅⊙⊙∘)
        ⊃(⋅⊙⊙∘
          +2
          ⊙⊡
          ≠
        | ⊙⊙⊙∘
        )
        =2+
      )
    )
  
    =0⊙⋅⋅◌CheckBounds Move?
  )

  /+
)
