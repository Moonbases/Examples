use reqwest::header::{HeaderMap, CONTENT_TYPE};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
struct LicenseRequest {
    product: String,
    license: String,
    hwid: String,
}
#[tokio::main]

async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let url = "http://localhost/api/license/authenticate";
    let body = LicenseRequest {
        product: "product_name".to_string(),
        license: "license_key".to_string(),
        hwid: "hardware_id".to_string(),
    };

    let client = reqwest::Client::new();
    let mut headers = HeaderMap::new();
    headers.insert(CONTENT_TYPE, "application/json".parse().unwrap());
    headers.insert("Authorization", "public_api_key".parse().unwrap());

    let resp = client
        .post(url)
        .headers(headers)
        .json(&body)
        .send()
        .await?;

    let content = resp.text().await?;
    println!("{}", content);
    
    Ok(())
}