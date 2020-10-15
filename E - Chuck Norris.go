package main

import "fmt"
import "os"
import "bufio"
import "strconv"

func ConvertASCII(input string) string {


    var output string
    rInput:= []rune(input)
    last:='N'

    for i:=0; i<len(input); i++ {

        fmt.Fprintln(os.Stderr, rInput[i])
        
        intValue:= int64(rInput[i])
        fmt.Fprintln(os.Stderr, intValue)

        binaryValue := strconv.FormatInt(intValue, 2)

        for len(binaryValue) < 7 {
            binaryValue = "0" + binaryValue
        }

        fmt.Fprintln(os.Stderr, binaryValue)

        rBinaryValue:= []rune(binaryValue)

        //Init
        j:=0
        if last =='N' {
            last:= rBinaryValue[0]
            if last=='1' {
                output+="0 0"
            } else if last=='0'{   
                output+="00 0"
            }
            j++
        }
    
        for j=j; j<len(binaryValue); j++ {
        
            current:=rBinaryValue[j]
            
            if current == last{
                output+="0"
                continue
            } 

            if current=='0' {
                 output+=" 00 0"
            } else if  current=='1'{       
                    output+=" 0 0"
            }  

            last = rBinaryValue[j]
        }

    }
    return output
}
    
func main() {


    scanner := bufio.NewScanner(os.Stdin)
    scanner.Buffer(make([]byte, 1000000), 1000000)
    scanner.Scan()
    MESSAGE := scanner.Text()

    fmt.Fprintln(os.Stderr, MESSAGE)


    fmt.Println(ConvertASCII(MESSAGE))// Write answer to stdout
}