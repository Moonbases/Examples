import requests
import json

body = {
    "product": "product_name",
    "license": "license_key",
    "hwid": "hardware_id",
}

headers = {
    "Content-Type": "application/json",
    "Authorization": "public_api_key",
}

res = requests.post("http://localhost/api/license/authenticate", headers=headers, json=body).json()

print(res.data)