import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class LicenseRequest {
  public String product;
  public String license;
  public String hwid;
}
public class Main {
  public static void main(String[] args) throws IOException {
    String url = "http://localhost/api/license/authenticate";
    LicenseRequest body = new LicenseRequest();

    body.product = "product_name";
    body.license = "license_key";
    body.hwid = "hardware_id";
    String apiKey = "public_api_key";

    URL obj = new URL(url);
    HttpURLConnection con = (HttpURLConnection) obj.openConnection();

    con.setRequestMethod("POST");
    con.setRequestProperty("Content-Type", "application/json");
    con.setRequestProperty("Authorization", apiKey);
    con.setDoOutput(true);

    OutputStream os = con.getOutputStream();
    os.write(new Gson().toJson(body).getBytes());
    os.flush();
    os.close();

    int responseCode = con.getResponseCode();
    BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
    String inputLine;
    StringBuffer response = new StringBuffer();

    while ((inputLine = in.readLine()) != null) {
      response.append(inputLine);
    }

    in.close();
    System.out.println(response.toString());
  }
}