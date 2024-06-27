package main

import (
	"bufio"
	"fmt"
	"math/big"
	"math/rand"
	"net"
	"os"
)

func handleConnection(conn net.Conn) {
	defer conn.Close()
	reader := bufio.NewReader(conn)
	for i := 0; i < 2048; i++ {
		n1 := big.NewInt(int64(rand.Int()))
		n2 := big.NewInt(int64(rand.Int()))
		n3 := big.NewInt(int64(rand.Int()))

		sol := big.NewInt(0)

		if i < 256 {
			sol.Add(n1, n2)
			conn.Write([]byte(fmt.Sprintf("[Difficulty LOW] [%v]: %v+%v: ", i, n1.String(), n2.String())))

		} else if i < 512 {
			sol.Add(n1, n2)
			sol.Add(sol, n3)
			conn.Write([]byte(fmt.Sprintf("[Difficulty MEDIUM] [%v]: %v+%v+%v: ", i, n1.String(), n2.String(), n3.String())))

		} else if i%4 == 0 {
			sol.Sub(n1, n2)
			conn.Write([]byte(fmt.Sprintf("[Difficulty MEDIUM] [%v]: %v-%V: ", i, n1.String(), n2.String())))
		} else if i%4 == 1 {
			sol.Add(n1, n2)
			conn.Write([]byte(fmt.Sprintf("[Difficulty MEDIUM] [%v]: %v+%V: ", i, n1.String(), n2.String())))
		} else if i%4 == 2 {
			tmp := big.NewInt(0).Add(n1, n2)
			sol.Sub(tmp, n3)
			conn.Write([]byte(fmt.Sprintf("[Difficulty MEDIUM] [%v]: %v+%V-%v: ", i, n1.String(), n2.String(), n3.String())))
		} else if i%4 == 3 {
			tmp := big.NewInt(0).Sub(n1, n2)
			sol.Add(tmp, n3)
			conn.Write([]byte(fmt.Sprintf("[Difficulty MEDIUM] [%v]: %v-%V+%v: ", i, n1.String(), n2.String(), n3.String())))
		}
		message, err := reader.ReadString('\n')
		if err != nil {
			fmt.Println("Client disconnected.")
			return
		}

		if len(message) > 0 {
			message = message[:len(message)-1]
		}

		userSol, ok := big.NewInt(0).SetString(message, 10)
		if !ok {
			conn.Write([]byte("Invalid number!"))
			return
		}
		if userSol.Cmp(sol) != 0 {
			conn.Write([]byte(fmt.Sprintf("Wrong! Expected: %v", sol.String())))
			return
		}
	}

	conn.Write([]byte("HCamp{B3tt3r_M1n3_Th1S_AnD_N0T_B1tC0iN}"))
}

func main() {
	listener, err := net.Listen("tcp", "0.0.0.0:20220")
	if err != nil {
		fmt.Println("Error starting TCP server:", err)
		os.Exit(1)
	}
	defer listener.Close()
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			continue
		}
		go handleConnection(conn)
	}
}
