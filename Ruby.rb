require 'httparty'

data = HTTParty.post(
    'http://localhost/api/license/authenticate',
    headers: {
        'Content-Type' => 'application/json',
        'Authorization' => 'public_api_key'
    },
    body: {
        product: 'product_name',
        license: 'license_key',
        hwid: 'hardware_id'
    }
)

puts data