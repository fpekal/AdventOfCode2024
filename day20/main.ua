# Experimental!

Input      ← &fras "input.txt"
ParseInput ← ⊃(°¤⊚=@S|°¤⊚=@E|=@#)⊜∘≠@\n.

GetAvailableNeighbours ← (
  ¤.
  [¯1_0 1_0 0_¯1 0_1]
  ≡+
  ⊙⋅⋅∘
  ⊙¤
  ⊃(⊙(¬≡⊡).
    ▽:
  )
)

ParseInput Input

⊃(⊙⊙∘
| astar(
    GetAvailableNeighbours
  | 1
  | ≍
  )
  °□⊡0
  +1:
  ⇡
  ≡(×°⊡¤?)
)

# ⊃(⊙∘
# | ⋅⋅∘
#  ⇡140_140
#  △.
#  [:2/×↙2]
#  ↯
#  ⊙¤
#  ≡(⍜⊡0)
# )

# ⊙⊙⊙◌
# ¤⊙¤
# ≡(
#  ◌astar(
#    GetAvailableNeighbours
#  | 1
#  | ≍
#  )
#  -
# 	?
# )
# /+▽≥100.⍆▽≠0.
