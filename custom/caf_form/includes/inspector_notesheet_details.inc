<?php
function inspector_notesheet_details($form, &$form_state,$app_id){
	global $base_root,$base_path,$user;
	$app_note_id 		= encryption_decryption_fun('decrypt', $app_id);
	
	$form = array();
	$form['header'] = array(
			'#markup' 	=> t('<div class="content"><div class="sky-form">'),
		);
	
	$form['notesheet_preview'] 	= array(
		'#type'		=> 'markup',
  		'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              			<h3 class="box-title">Display Notesheet Details</h3>
			    		</div>',
						);
	
				
	$form['notesheet_preview']['markup_appplication'] = array(
		'#prefix' 	 => '<div class="col-md-12 col-xs-12">',
  		'#suffix' 	 => '</div>',
		'#type' 			=> 'markup',
		'#markup' 			=>notesheet_data_details($app_note_id),
		);
		
	$form['back_link']	 = array(
		'#prefix' => '<div align="left">',
		'#suffix' => '</div></div>',
		'#markup' 		=> l(t('Back'),'', array('html' => TRUE,'attributes'=> array('class'=>array('btn btn-info ')))),
			);

return $form;
}
function notesheet_data_details($app_note_id){
	global $base_root,$base_path,$user;		
	
	$note_details =  get_notesheet_data_details($app_note_id);
	foreach($note_details as $data){
		$application_id 	= $data->application_no;
		$service_id 		= $data->service_id;
		$factory_type_id 	= $data->factory_type_id;
		$reference_no 		= $data->referance_no;
	$content = '<style type="text/css">
				table {
					font-family: arial, sans-serif;
					border-collapse: collapse;
					width: 100%;
					
					}
				td, th {
					border: 1px solid #fff;
					text-align: left;
					padding: 5px !important;
					}
				
				</style>';
	
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">1. </td>
						<td width="15%"  align="left" valign="top" style="font-size:12px;">Date of Visit: </td>
						<td width="80%" align="left" valign="top" style="font-size:12px;"><b>'.date('dS M Y', strtotime($data->visit_date)).'</b></td>
					</tr>
				</table>';
				
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">2. </td>
						<td width="98%"  align="left" valign="top" style="font-size:12px;">In case of new or existing factory coming under the purview of the Act: </td>
					</tr>
					</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="1%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="50%" align="left" valign="top" style="font-size:12px;">(a) Date of starting: <b>'.date('dS M Y', strtotime($data->factory_starting)).'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(b) Date of Amenability: <b>'.date('dS M Y', strtotime($data->factory_amenabity_date)).'</b></td>
					</tr>
				</table>';
				
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">3. </td>
						<td width="98%"  align="left" valign="top" style="font-size:12px;">In case of an old registered factory crossed/closed down /shifted- : </td>
					</tr>
					</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="50%" align="left" valign="top" style="font-size:12px;">(a) Registn No.: <b>'.$data->close_reg_no.'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(b) Date of Restarting: <b>'.date('dS M Y', strtotime($data->date_restart)).'</b></td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="50%" align="left" valign="top" style="font-size:12px;">(c) Date of crossed off/ Closed down / shifting: <b>'.date('dS M Y', strtotime($data->date_cossed)).'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(d) Date of Amenability: <b>'.date('dS M Y', strtotime($data->date_shift_amenability)).'</b></td>
					</tr>
				</table>';
	$get_fa_cafa           	= 	get_fa_cafa($application_id);
	$getdata_owner_address 		 =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				 =	$get_fa_cafa['addrline_premises'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_owner_address);
	//$occupier_last_slab_display = get_occupier_last_slab($application_id,$service_id,$factory_type_id,$reference_no);
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
	
						<tr>
							
							<td width="30%"  style="font-size:12px;" colspan="2">4.Comments on information furnished relating to owner and occupier of promises / Factory: </td>
						</tr>
						<tr>
						<td colspan="4"></td>
						</tr>
						<tr>
						<td width="30%"  align="left" style="font-size:12px;" colspan="2">Comments on information furnished relating to owner of promises / Factory: </td>
						</tr>
						<tr>
						<td colspan="2"></td>
						</tr>
						<tr>
							
							<td width="2%"   valign="top" style="font-size:12px;">Name</td>
							<td width="30%"  style="font-size:12px;"><b>'.$get_fa_cafa['owner_name'].'</b></td>
						</tr>
						<tr>
						<td colspan="2"></td>
						</tr>
						<tr>
							<td width="30%"   valign="top" style="font-size:12px;">Address</td>
							<td width="30%"  style="font-size:12px;"><b>'.$owner_address.'</b></td>
						</tr>
						<tr>
						<td colspan="2"></td>
						</tr>
						<td width="30%"  align="left" style="font-size:12px;" colspan="2">Comments on information furnished relating to occupier of promises / Factory: </td>
						<tr>
						<td colspan="2"></td>
						</tr>';
						if(!empty($occupier_last_slab_display)){
					foreach($occupier_last_slab_display as $details){
						$type 		    = $details->type_director;
						$is_occupier 	= $details->is_occupier;
						if($is_occupier == 1){
							$occupier = '-(Occupier)';
						}
						$fieldArr_director =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    				$address_of_director   =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
					$occupier_deatils		=	$$details->name_director.'<br/>Father/Husband name:-'.$details->father_husband_name_director.'<br/>Age:-'.$$details->age_director.'(Year)';
						$content .= '<tr>
							<td width="30%"   valign="top" style="font-size:12px;">Details</td>
							<td width="30%"  style="font-size:12px;"><b>'.$occupier_deatils.'</b></td>
						</tr>
						<tr>
							<td width="30%"   valign="top" style="font-size:12px;">Residential Address</td>
							<td width="30%"  style="font-size:12px;"><b>'.$address_of_director.'</b></td>
						</tr>';
						}}
				$content .= '</table>';				
				
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">5. </td>
							<td width="98%"  align="left" style="font-size:12px;">Name / Names of major products in order of volume of production: </td>
						</tr>
					</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">';
	// $volume_production =  substr($data->volume_production,1,-1);
	//$list_data=  (explode(",",$volume_production));
	//$x = 'a';
	
	$get_manufacturing = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($get_manufacturing);die();
	
	$i=1;
	foreach($get_manufacturing as $lst){

	$content .=	'<table class="table table-bordered"> 
											<tr>
     										<th>Nature of manufacturing process</th>
	 										<th>Nic code</th>
	 										</tr>
											<tr>
     										<td>'.$lst->nature_manufacturing.'</td>
	 										<td>'.$lst->nic_sub_code.'</td>
											</tr>';
	$i++;
	}			
	$content .= '</table>';
	
					
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">6.</td>
							<td width="98%"  align="left" style="font-size:12px;">Nature and amount of installed power(KW/HP): <u><b>'.$data->power_install.'</b></u></td>
						</tr>
				</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">7.</td>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">(a)</td>
							<td width="96%" align="left" style="font-size:12px;">Maximum No. of workers employed on any day during the years preceeding the year of registration:  <u><b>'.$data->worker.'</b></u></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">(b)</td>
							<td width="96%" align="left" style="font-size:12px;">Number of workers on date of amenability: <u><b>'.$data->worker_at_amen.'</b></u></td>
						</tr>
					</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">8.</td>
							<td width="98%" align="left" style="font-size:12px;">Approval No. <u><b>'.$data->approval_no.'</b></u> Date <u><b>'.$data->approval_no_date.'</b></u> of site and plans if approved, otherwise comments on confirmity of the site & building to be Act. </td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px;"><u>__</u></td>
						</tr>
					</table>';
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">9.</td>
							<td  width="98%" align="left" style="font-size:12px;">any other additional comment that the inspector may like to add relation to health hazards and safty, effluent disposal, approval of appropriate authority in respect of storage of inflammable liquids, gases etc. approval form environmental pollution department.</td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px; text-transform:uppercase;">Category &nbsp;&nbsp;<u><b>'.$data->category.'</b> </u>&nbsp;&nbsp; Reference Number &nbsp;&nbsp; <u>'.$data->category_ref.'</u>&nbsp;&nbsp; Approval date &nbsp;&nbsp; <u>'.date('dS M Y', strtotime($data->category_date)).'</u>
							</td>
							
						</tr>
					</table>';
		$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">10.</td>
							<td width="98%" align="left" style="font-size:12px;">Recommended for registration under classification <u><b>'.$data->classification.'</b></u>  category <u><b>'.$data->classification_category.'</b></u>  NEW, w.e.f. <u><b>'.$data->amenability.'</b></u> as also grant and issue of licence after renewing if for upto H.P. <u><b>'.$data->hp.'</b></u> and worker upto <u><b>'.$data->worker_year.'</b></u> valid upto date <u><b>'.$data->last_year.'</b></u>.</td>
						</tr>
						<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">11.</td>
						<td width="98%" align="left" style="font-size:12px;">E-note:- &nbsp;&nbsp;'.$data->addition_remark.'</td>
						</tr>
					</table>';	
				}

	return $content;
	
	}
	