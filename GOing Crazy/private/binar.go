
//HCamp{G0_15_fun_n0t_g0nn4_l13}

package main

import (
    "crypto/rc4"
    "encoding/hex"
    "fmt"
    "io"
    
)

const (
    EncryptedFlagHex = "b308e7b6dac4a2d9af921646c26b25c8456fb111b40cde89970648bbf1f4"
    KeyHex           = "238faeb6389c9d150ebc"
)

func main() {
    // Convert hex encoded strings to byte slices
    encryptedFlag, err := hex.DecodeString(EncryptedFlagHex)
    if err != nil {
        fmt.Printf("Error decoding hex: %v\n", err)
        return
    }

    key, err := hex.DecodeString(KeyHex)
    if err != nil {
        fmt.Printf("Error decoding hex: %v\n", err)
        return
    }

    // Create an RC4 cipher
    cipher, err := rc4.NewCipher(key)
    if err != nil {
        fmt.Printf("Error creating RC4 cipher: %v\n", err)
        return
    }

    // Decrypt the encrypted flag
    decryptedFlag := make([]byte, len(encryptedFlag))
    cipher.XORKeyStream(decryptedFlag, encryptedFlag)

    // Read user input
    fmt.Print("Enter the flag: ")
    var userInput string
    _, err = fmt.Scanln(&userInput)
    if err != nil && err != io.EOF {
        fmt.Printf("Error reading input: %v\n", err)
        return
    }

    // Compare input with decrypted flag
    if userInput == string(decryptedFlag) {
        fmt.Println("Correct! You got the flag.")
    } else {
        fmt.Println("Incorrect flag. Try again.")
    }
}
