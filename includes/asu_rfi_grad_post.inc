<?php

function asu_rfi_grad_post($data){
  global $base_url;
  dpm($data);
  $fname = $data['first_name'];
  $lname = $data['last_name'];
  $email = $data['email'];
  $phone = preg_replace('[\D]', '',$data['phone']);
  $term = $data['semester_name'];
  $state = $data['state'];
  
  $nodeid = $data['submission_nodeid'];
 
  //check if the submission values are empty
  if(isset($state)){
    $state_province = $state;
  }
  else{
    $state_province = '';
  }
  
  
  //date of birth
  if(isset($data['dob'])){
    $dob = $data['dob'];
  }
  else{
    $dob = '';
  }
  
  //Military
  if(isset($data['military'])){
    $military = $data['military'];
  }
  else{
    $military =  '';
  }
 
 //Comment
  if(isset($data['comment'])){
    $comment = $data['comment'];
  }
  else{
    $comment = '';
  }
  
  //city
  if(isset($data['city'])){
    $city = $data['city'];
  }
  else{
    $city = '';
  }
  
  //country
  if(isset($data['country'])){
    $country = $data['country'];
  }
  else{
    $country = '';
  }

  //Get siteDomain variable to see if it's dev or qa site.
  $site = variable_get('siteDomain');

   // Salesforce URL to post data to
  if(($site == "dev") || ($site == "qa")){
     $url = 'https://requestinfo-qa.asu.edu/prospect_form_post'; 
  }
  else{
    $url = 'https://requestinfo.asu.edu/prospect_form_post'; 
  }
  
$source = '';
   

$headers = array('Content-Type' => 'application/x-www-form-urlencoded');  
  
  // build data array to post
  $submission_data = array (
		'source'=> $source,
		'firstName'=> $data['first_name'],
		'lastName'=> $data['last_name'],
		'emailAddress'=> $data['email'],
		'phoneNumber'=> $phone,
		'projectedEnrollment'=> $data['semester_name'],
                'addressLine1' => $data['address'],
                'city' => $city,
                'state' => $state_province,
                'countryOfCitizenship' => $country,
                'birthdate' => $dob,
                'veteranStatus' => $military,
                'questions' => $comment,
		'poiCode' => $data['prog_plan'],
		
	);
  
 
foreach($submission_data as $key_value => $result_array){
    if(($result_array == "None")){
   
      unset($submission_data[$key_value]);
      
    }
}

// build the URL encoded
$at = http_build_query($submission_data, '', '&');  
   
// post the data
$options = array(
                'method' => 'POST',
                'data' => $at,
                'timeout' => 90,
                'headers' => $headers,
                 );
    
$response = drupal_http_request($url, $options); // send the response
dpm($response, "response from Salesforce");

//Get the previous page node
$destination = drupal_get_destination();

//$data_options = $_SESSION['rfi_data'];

//append previous page node and append it to base url
$goto_url = $base_url .'/'.$destination['destination'];


if($response->code == 400) {
		//$options = array('query' => array('fname' => $fname, 'lname' => $lname, 'email' => $email, 'phone' => $phone, 'term' => $term, 'current_prev_student' => $current_prev_student));
		drupal_set_message( "Please fix the following issue and try submitting the form again:<br />" . $response->data, 'error');
              //  drupal_goto($goto_url, $data_options );
                $status = "Incomplete";
}
if($response->code == 500) {
		drupal_set_message($response->data . "<br />We have an issue with our form, and we’re working on fixing it. We apologize for the inconvenience. In the meantime, please send an email to <a href='mailto:gograd@asu.edu'>gograd@asu.edu</a> about your interest in graduate studies, and we will be glad to get you the information you need to take your next steps. Thank you.", 'error');
		 $status = "Pending";
               //  unset($_SESSION['rfi_data']);
}



//Get the response from Salesforce. If the submission is not successfull, update the previous submission status to Incomplete
if(($response->code == 400) || ($response->code == 500)){
    		
  $node_status_updated = db_update('field_data_field_rfi_submission_status') 
  ->fields(array(
    'field_rfi_submission_status_value' => $status,
  ))
  ->condition('entity_id', $nodeid)
  ->execute();
  //Clear cache on field to display field's updated value on front end        
  $cid = 'field:node:' . $nodeid;
  cache_clear_all($cid, 'cache_field');
}

if(($response->code == 200) || ($response->code == -110)){
    //unset($_SESSION['rfi_data']);
    $node_status_updated = db_update('field_data_field_rfi_submission_status') 
  ->fields(array(
    'field_rfi_submission_status_value' => 'SF_Complete',
  ))
  ->condition('entity_id', $nodeid)
  ->execute();
  //Clear cache on field to display field's updated value on front end        
  $cid = 'field:node:' . $nodeid;
  cache_clear_all($cid, 'cache_field');
}


}

?>