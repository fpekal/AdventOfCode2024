# Experimental!

Input        ← &fras "input.txt"
ParseInput   ← ⊜(≡(=@#))≠@\n.
GetPositions ← °¤⊙°¤⊃(⊚=@S|⊚=@E)⊜∘≠@\n.

ParseInput Input
GetPositions Input

DirToVec ← ⨬(¯1_0|0_1|1_0|0_¯1)

⊂:1

astar(
  ⊃(↯2_3
    ¯1_1
    ≡⍜(↙¯1:|◿4+)
    ≡(1000∘)
  | ⊃(⊃(°¤↙¯1|↘¯1)
      +DirToVec
    | ⊙⊙∘
    )
    ⊃(⊡⊙⋅⋅∘|⊙⊙⊙∘)
    ⊃(⊙⋅◌|⊃(⊂:↙¯1:|⋅∘)⋅∘)
    ⨬([1]∘|[][])
  )

  ⊃(⊂⋅⊙⋅∘|⊂⊙⋅⊙◌)
  ⊙⊙⋅⋅◌
  :
| ℂ°⊟↘¯1
  ⊙(ℂ°⊟)
  ⌵-
| ≍↙2
)

⊃( # Part 1
  ∘◌
| # Part 2
  ⊙◌
  ≡(□≡(↘¯1)°□)
  ≡(°⊚°□)
  # ≡&ims
  /+
  >0
  /+/+
)
