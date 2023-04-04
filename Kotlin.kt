import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.module.kotlin.registerKotlinModule
import com.github.kittinunf.fuel.Fuel
import com.github.kittinunf.fuel.core.extensions.authentication
import com.github.kittinunf.fuel.core.Headers
import com.github.kittinunf.fuel.core.Method

data class LicenseRequest(val product: String, val license: String, val hwid: String)

fun main() {
  val url = "http://localhost/api/license/authenticate"
  val body = LicenseRequest("product_name", "license_key", "hardware_id")
  val mapper = ObjectMapper().registerKotlinModule()
  val json = mapper.writeValueAsString(body)
  
  Fuel.request(Method.POST, url)
    .body(json)
    .authenticate("public_api_key", "")
    .header(Headers.CONTENT_TYPE, "application/json")
    .responseString { _, _, result ->
      result.fold(
        { data ->
          println(data)
        },
        { error ->
          println(error)
        }
      )
    }
}