package main

import "fmt"

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

func main() {

    // lightX, lightY: the X and Yposition of the light of power
    // initialTx, initialTy: Thor's starting X and Y position

    var lightX, lightY, initialTx, initialTy int
    fmt.Scan(&lightX, &lightY, &initialTx, &initialTy)
    
    for {

        var remainingTurns int
        var output string
        fmt.Scan(&remainingTurns)

        output=""

        if (initialTy - lightY) > 0 {
        output+="N"
        initialTy--
        } else if (initialTy - lightY) < 0 {
        output+="S"
        initialTy++
        }

       if (initialTx - lightX) > 0 {
        output+="W"
        initialTx--
        } else if (initialTx - lightX) < 0 {
        output+="E"
        initialTx++
        }   
        
        // A single line providing the move to be made: N NE E SE S SW W or NW
        fmt.Println(output)
    }
}