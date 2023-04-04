using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

public class LicenseRequest {
  public string product { get; set; }
  public string license { get; set; }
  public string hwid { get; set; }
}

public class MainClass {
  public static async Task Main() {
    string url = "http://localhost/api/license/authenticate";
    LicenseRequest body = new LicenseRequest {
      product = "product_name",
      license = "license_key",
      hwid = "hardware_id"
    };
    
    string apiKey = "public_api_key";

    var client = new HttpClient();
    var jsonBody = JsonSerializer.Serialize(body);
    var content = new StringContent(jsonBody, Encoding.UTF8, "application/json");

    content.Headers.Add("Authorization", apiKey);

    var response = await client.PostAsync(url, content);
    var responseAsString = await response.Content.ReadAsStringAsync();
    
    Console.WriteLine(responseAsString);
  }
}