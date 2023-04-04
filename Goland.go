package main

import (
    "bytes"
    "encoding/json"
    "fmt"
    "net/http"
)

type LicenseRequest struct {
    Product string `json:"product"`
    License string `json:"license"`
    Hwid    string `json:"hwid"`
}

func main() {
    url := "http://localhost/api/license/authenticate"

    body := &LicenseRequest{
        Product: "product_name",
        License: "license_key",
        Hwid:    "hardware_id",
    }
	
    jsonBody, _ := json.Marshal(body)

    req, _ := http.NewRequest(http.MethodPost, url, bytes.NewBuffer(jsonBody))
    req.Header.Set("Content-Type", "application/json")
    req.Header.Set("Authorization", "public_api_key")

    client := http.Client{}
    resp, err := client.Do(req)

    if err != nil {
        fmt.Println(err)
        return
    }

    defer resp.Body.Close()
    var result map[string]interface{}
    err = json.NewDecoder(resp.Body).Decode(&result)

    if err != nil {
        fmt.Println(err)
        return
    }

    fmt.Println(result)
}