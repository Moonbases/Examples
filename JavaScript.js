const axios = require('axios');

const options = {
  method: 'POST',
  url: 'http://localhost/api/license/authenticate',
  headers: {
    'Content-Type': 'application/json',
    'Authorization': 'public_api_key'
  },
  data: {
    product: 'product_name',
    license: 'license_key',
    hwid: 'hardware_id'
  }
};

axios(options)
  .then(response => {
    console.log(response.data);
  })
  .catch(error => {
    console.error(error);
  });