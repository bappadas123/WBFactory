<?php
function form19_view( $formid ,$referenceid, $factorytypeid, $serviceid){	

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
    $service_id 	= encryption_decryption_fun('decrypt', $serviceid);


	$get_all_data 		= get_dangerous_occurence_details($form_id,$reference_id,$factory_typeid,$service_id);
	$get_occurence_data = get_occurence_data($form_id);
	
	$form = array();
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3 style="text-align: center;"><b>Application for Approval of Plan</b><p style="text-align: right;">'.$uploaded_pdf_link.'</p><p style="font-size:15px;" class="text-green">'.$application_no.'</p></h3>'),
	);

 	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              <div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title pull-left">Application View - Dangerous Occurrence (FORM-19)</h3>
              <p class="pull-right" style="text-align:right;">'.$uploaded_pdf_link.'</p>
              </div></div>
			  <div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12">
			  <table class="table table-bordered custom-table-view"> <tr>
   								<th width="40%">Parameters</th>
   								<th>Inputs</th>
								</tr>';

	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_all_data[0]->factory_name.'</td></tr>
				<tr><td>(ii) Nature of the Industry</td><td>'.$get_all_data[0]->industry_nature.'</td></tr>
				<tr><td>(iii) Registration No.</td><td>'.$get_all_data[0]->registration_number.'</td></tr>
				<tr><td>(iv) Registration Date</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->registration_date)).'</td></tr>
				<tr><td>(v) Licence No.</td><td>'.$get_all_data[0]->licence_number.'</td></tr>
				<tr><td>(vi) Licence Date</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->licence_date)).'</td></tr>
				<tr><td>(vii) Classification No.</td><td>'.$get_all_data[0]->classification_no.'</td></tr>
				<tr><td>(viii) Date and hour of dangerous occurrence</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->date_occurrence)).' at '.$get_all_data[0]->time_occurrence.'</td></tr>
				<tr><td>(ix) Full account of dangerous occurrence</td><td>'.$get_all_data[0]->full_account.'</td></tr>
				<tr><td>(x) Branch or department where the dangerous occurrence occured</td><td>'.$get_all_data[0]->branch_name.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">B. Name of person who saw the dangerous occurrence and can give important evidence</td></tr>';
				
			$i = 0;
			while($i < count($get_occurence_data))
			{ $slno = $i+1;
	$output .='
				<tr><td>('.$slno.') Name of person</td><td>'.$get_occurence_data[$i]->persons_name.'</td></tr>';
				$i++;			 
			}			
				
	$output .= '</table></div></div></div></div>';
	return $output;
 }