<?php

function asu_rfi_grad_post($data){
    dpm($data);
    
    
  $authkey = variable_get(asu_rfi_form_auth_key, 'NULL');
  $fname = $data['fname'];
  $lname = $data['lname'];
  $email = $data['email'];
  $phone = preg_replace('[\D]', '',$data['phone']);
  $term = $data['semester'];
  $state = $data['state'];
  $program_code = $data['program_plan'];
  $province = $data['province'];
  if(isset($state)){
    $state_province = $state;
  }
  else{
    if(isset($province)){
        $state_province = $province;
    }
  }
$secret_key = sha1($email . $program_code . $authkey);
$source = '';
   
// Salesforce URL to post data to
$url = "https://webforms.asu.edu/asu_rfi_dedupe/submit_rfi/$secret_key/$nid"; 
$headers = array('Content-Type' => 'application/x-www-form-urlencoded');

//Initiate cURL.
$ch = curl_init($url);
 
//The JSON data.
/*$jsonData = array(
    'username' => 'MyUsername',
    'password' => 'MyPassword'
);
 
//Encode the array into JSON.
$jsonDataEncoded = json_encode($jsonData);
 
//Tell cURL that we want to send a POST request.
curl_setopt($ch, CURLOPT_POST, 1);
 
//Attach our encoded JSON string to the POST fields.
curl_setopt($ch, CURLOPT_POSTFIELDS, $jsonDataEncoded);
 
//Set the content type to application/json
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json')); 
 
//Execute the request
$result = curl_exec($ch);
 */ 
  // build data array to post
 /* $submission_data = array (
		'source'=> $source,
		'firstName'=> $data['fname'],
		'lastName'=> $data['lname'],
		'emailAddress'=> $data['email'],
		'phoneNumber'=> $phone,
		'projectedEnrollment'=> $data['semester'],
                'addressLine1' => $data['address'],
                'city' => $data['city'],
                'state' => $state_province,
                'countryOfCitizenship' => $data['country'],
                'birthdate' => $data['dob'],
                'veteranStatus' => $data['military'],
                'questions' => $data['comment'],
		//'currentPrevStudent'=> $current_prev_student,
		//'url' => "https://requestinfo.asu.edu/node/16",
		'poiCode' => $data['program_plan'],
		
	);
  
foreach($submission_data as $key_value => $result_array){
    if(($result_array == "None")){
   
      unset($submission_data[$key_value]);
      
    }
}
dpm($submission_data);
// build the URL encoded
$at = http_build_query($submission_data, '', '&');  
   
// post the data
$options = array(
                'method' => 'POST',
                'data' => $at,
                'timeout' => 90,
                'headers' => $headers,
                 );
    

*/
}

?>