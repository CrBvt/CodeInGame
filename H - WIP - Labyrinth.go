package main
	
import (
    "fmt"
    "os"
)

type Bitmask uint32

const (
	UP Bitmask = 1
	RIGHT Bitmask = 2
	DOWN Bitmask = 4
    LEFT Bitmask = 8

    BELOW Bitmask = 0
    ONE Bitmask = 1
    ABOVE Bitmask = 16
)

func ConvertLab (char rune) int {
    
    switch char {
        case '?':
            return 0
        case '.':
            return 1
        case '#':
            return 2
        case 'C':
            return 5
        case 'T':
            return 8
    }
    return 0
}

func ConvertMove(iMove Bitmask) string {

    switch iMove{
        case UP:
            return "UP"
        case DOWN:
            return "DOWN"
        case LEFT:
            return "LEFT"
        case RIGHT:
            return "RIGHT"
    }
    return "N/A"
}

func CheckCell(labyrinth [][]int, Y int, X int, isValid* bool, isSolved* bool) int {

    switch labyrinth[Y][X] {

    case 2 :
        *isValid= false
        return 0
    case 5 :
        *isSolved = true
    }

    *isValid = true
    return 1
}


func HugWall(iValidOutput Bitmask, iMove Bitmask, wall Bitmask) Bitmask {

    var valid Bitmask = 0

    //Direction from where we are from
    switch iMove {
        case UP:
            iMove = DOWN
        case DOWN:
            iMove = UP
        case LEFT:
            iMove = RIGHT
        case RIGHT:
            iMove = LEFT
    }

    //Wall we wish to stick to
    switch wall{

        case LEFT :

            for valid < ONE {
                  
                iMove = iMove << ONE
                if iMove == ABOVE { iMove = UP }
                valid = iValidOutput & iMove
            }    

        case RIGHT :

            for valid < ONE {

                iMove = iMove >> ONE
                if iMove == 0 { iMove = LEFT }
                valid = iValidOutput & iMove
            }
    }

    return iMove
}

func Backtrack(labyrinth [][]int, visited [][]bool, KR int, KC int, R int, C int) Bitmask {

    if KR+1<R  { if visited[KR+1][KC] == true { return DOWN  } }
    if KR-1>=0 { if visited[KR-1][KC] == true { return UP    } }
    if KC+1<C  { if visited[KR][KC+1] == true { return RIGHT } }
    if KC-1>=0 { if visited[KR][KC-1] == true { return LEFT  } }

    return 0
}

func main() {
    // R: number of rows.
    // C: number of columns.
    // A: number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    var R, C, A int

    isSolved:=false
    isDone:=false
    isValid:=false

    var iValidOutput Bitmask = 0
    var iMove Bitmask = UP

    fmt.Scan(&R, &C, &A)

    fmt.Fprintln(os.Stderr, R)
    fmt.Fprintln(os.Stderr, C) 

    labyrinth := make([][]int, R)
    for i := 0; i < R; i++ { labyrinth[i] = make([]int, C) }

    visited := make([][]bool, R)
    for i := 0; i < R; i++ { visited[i] = make([]bool, C) }

    for {
        // GET POSITION
        var KR, KC int
        fmt.Scan(&KR, &KC)

        //CHECK BACKTRACKING
        isBacktracking:=visited[KR][KC]
        if !isDone { 
            visited[KR][KC]=true 
        } else { visited[KR][KC]= false  }

        //LOAD LAB
        for i := 0; i < R; i++ {

            var ROW string
            fmt.Scan(&ROW)
            rRow := []rune(ROW)

            for j :=0; j< C;j++{
                x:=ConvertLab(rRow[j])  
                if x > 0 { labyrinth[i][j]=x }                   
            }

            fmt.Fprintln(os.Stderr, labyrinth[i]) 
        }

        //CHECK NEIGHBOOR CELLS
        iValidOutput = 0
        if KR+1<R  { if CheckCell(labyrinth,KR+1,KC,&isValid, &isSolved) > 0 { iValidOutput+=DOWN  } }
        if KR-1>=0 { if CheckCell(labyrinth,KR-1,KC,&isValid, &isSolved) > 0 { iValidOutput+=UP    } }
        if KC+1<C  { if CheckCell(labyrinth,KR,KC+1,&isValid, &isSolved) > 0 { iValidOutput+=RIGHT } }
        if KC-1>=0 { if CheckCell(labyrinth,KR,KC-1,&isValid, &isSolved) > 0 { iValidOutput+=LEFT  } }

        //CHECK IF CONTROL ROOM IS AROUND
        if isSolved && !isDone { 

            if KR+1<R  { if labyrinth[KR+1][KC] == 5 { iMove = DOWN  } }
            if KR-1>=0 { if labyrinth[KR-1][KC] == 5 { iMove = UP    } }
            if KC+1<C  { if labyrinth[KR][KC+1] == 5 { iMove = RIGHT } }
            if KC-1>=0 { if labyrinth[KR][KC-1] == 5 { iMove = LEFT  } }

            isDone=true
            //MOVE INTO CONTROL ROOM
            fmt.Println(ConvertMove(iMove))
            continue
        } 
        
        if isSolved && isDone{
            iMove = Backtrack(labyrinth, visited, KR, KC, R, C) 
        } else { 

            if isBacktracking {

                switch iMove {
                    case UP :
                        visited[KR+1][KC]= false
                    case RIGHT :
                        visited[KR][KC-1]= false
                    case DOWN :
                        visited[KR-1][KC]= false
                    case LEFT :
                        visited[KR][KC+1]= false
                }   
            }

            iMove = HugWall(iValidOutput,iMove, RIGHT) 
        }

        fmt.Println(ConvertMove(iMove))  
    }
}

 //fmt.Fprintln(os.Stderr, iOutput)

 /*labyrinth := make([][]int, R)
    rows := make([]int, R*C)
    for i := 0; i < R; i++ { labyrinth[i] = rows[i*C : (i+1)*C] }*/