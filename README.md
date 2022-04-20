## tic-tac-toe-cpp
Tic Tac Toe Game for two players as well as single player (play against computer)


#### Time and Space complexity analysis of Part A (two-player game) and Part B (against the computer where the computer is playing optimally)


Part A :
```
- For the board of arbitrary size n * n, we need to maintain 4 container - One for each direction. 
- So we will need total space for 4 * n elements. 

That makes the worst case space complexity O(n * 4) or O(n)

- Each move of a player is a constant operation. 
- Checking the win of a player along rows or columns is also a constant operation. 
- For detecting win across either diagonal though, we need to iterate over both containers, to sum up, all elements.
- For the board of size n, we need to perform traversal twice. 
- Thus time complexity for detecting a win in tic-tac-toe is O(2 * n) or simple O(n).  
- For the board of size n, we need to perform traversal twice. 

Thus time complexity for detecting a win in tic-tac-toe is O(2 * n) or simple O(n).
```


Part B :
```
- Min-Max algorithm performs complete depth-first exploration of the game tree. 
- If maximum depth of tree is `m` (9 for Tic-Tac-Toe)  and there are `b` legal moves at each node.
- Thus the time complexity of the MINIMAX algorithm is `O(bm)` and the space complexity is `O(m)`. 
- As the time complexity is exponential, this algo is impractical for games that are moderately more complex than Tic-Tac-Toe.
```

Note : The implementation handles edge cases properly and has validation checks against invalid inputs
