defmodule LicenseRequest do
  @derive Jason.Encoder
  defstruct [:product, :license, :hwid]
end

defmodule Main do
  require HTTPoison

  @url "http://localhost/api/license/authenticate"
  @body LicenseRequest[product: "product_name", license: "license_key", hwid: "hardware_id"]
  @headers [
    {"Content-Type", "application/json"},
    {"Authorization", "public_api_key"}
  ]

  def main(_) do
    response =
      HTTPoison.post(
        @url,
        Jason.encode!(@body),
        @headers,
        timeout: 5000 # in ms
      )

    IO.puts response.body
  end
end
