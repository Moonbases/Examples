PerformHttpRequest(
    "http://localhost/api/license/authenticate",
    function(errorCode, resultData, headers)
        data = json.decode(resultData)
        print(data)
        end
    end,
    "POST",
    json.encode({
        product = 'product_name'
        licensekey = 'license_key',
        hwid = 'hardware_id'
    }),
    {
        ['Content-Type'] = 'application/json',
        ['Authorization'] = 'public_api_key'
    }
)