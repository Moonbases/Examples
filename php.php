<?php

$url = 'http://localhost/api/license/authenticate';
$ch = curl_init($url);

$body = json_encode([
    'product' => 'product_name'
    'license' => 'license_key',
    'hwid' => 'hardware_id',
]);

curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, $body);
curl_setopt($ch, CURLOPT_HTTPHEADER, [
  'Content-Type: application/json',
  'Authorization: public_api_key'
]);

$json = curl_exec($ch);
$data = json_decode($json);

echo $data;