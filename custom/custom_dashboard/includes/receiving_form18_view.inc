<?php
function receiving_form18_view($form, &$form_state,$formid ,$referenceid, $factoryid){	

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_id 	    = encryption_decryption_fun('decrypt', $factoryid);

	$get_all_data 	    = get_notice_accident_data($form_id,$reference_id,$factory_id);
	$get_witness_data   = get_accident_witness_data($form_id);
	$get_injured_data   = get_accident_injured_person_data($form_id);// echo "<pre>".print_r($get_injured_data);
	
	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_notice_full_address('fa_form18_notice_accident','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);

 	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
	           <div class="col-lg-12 col-md-12 col-sm-12">
	           <table class="table table-bordered custom-table-view"> <tr>
   								<th width="6%" align="center">Sl No.</th>
								<th width="54%">Parameters</th>
   								<th width="45%">Inputs</th>
								</tr>';
								
		$output .='<tr>
			<td>1.</td>
			<td>Name of occupier (or Factory) Employer :</td>
			<td>'.ucfirst($get_all_data[0]->name_occupier).' ('.$get_all_data[0]->factory_name.')</td>
		 </tr>
		 <tr>
			<td>&nbsp;</td>
			<td>E.S.I Employer Code No. :</td>
			<td>'.$get_all_data[0]->esi_code.'</td>
		 </tr>
		 <tr>
			<td>2.</td>
			<td>Address of factory/premises where accident took place :</td>
			<td>'.$factory_address.','.$get_all_data[0]->addrline.'<br>Landmark : '.$get_all_data[0]->nearest_landmark.'</td>
		 </tr>
		 <tr>
			<td>3.</td>
			<td>Nature of industry :</td>
			<td>'.$get_all_data[0]->industry_nature.'</td>
		 </tr>
		 <tr>
			<td>4.</td>
			<td>Branch or department and exact place where the accident took place :</td>
			<td>'.$get_all_data[0]->branch_name.'<br>'.$get_all_data[0]->accident_place.'</td>
		 </tr>
		 <tr>
			<td>5. </td>
			<td>Name and address of the injured :</td>
			<td>'.$get_injured_data[0]->accident_person_name.'<br>'.$get_injured_data[0]->accident_person_address.'</td>
		 </tr>
		 <tr>
			<td>&nbsp;</td>
			<td>E.S.I Insurance No :</td>
			<td>'.$get_injured_data[0]->insurance_number.'</td>
		 </tr>
		 <tr>
			<td>6.</td>
			<td>(a) Sex :</td>
			<td>'.$get_injured_data[0]->gender.'</td>
		 </tr>
		 <tr>
			<td>&nbsp;</td>
			<td>(b) Age (last birthday) :</td>
			<td>'.$get_injured_data[0]->age.'</td>
		 </tr>
		 <tr>
			<td>&nbsp;</td>
			<td>(c) Occupation of the injured person :</td>
			<td>'.$get_injured_data[0]->accident_person_occupation.'</td>
		 </tr>
		 <tr>
			<td>7.</td>
			<td>Local E.S.I. Office to which the injured person is attached :</td>
			<td>'.$get_injured_data[0]->local_esi_office.'</td>
		 </tr>
		 <tr>
			<td>8.</td>
			<td>Date shift and hour of accident :</td>
			<td>'.$get_all_data[0]->accident_date.' in '.$get_all_data[0]->accident_shift.' at '.$get_all_data[0]->accident_time.'</td>
		 </tr>
		 <tr>
			<td>9.</td>
			<td>(a) Hour at which the injured person started work on the day of accident :</td>
			<td>'.$get_injured_data[0]->local_esi_office.'</td>
		 </tr>
		 <tr>
			<td>&nbsp;</td>
			<td>(b) Whether wages in full Or part are payable to him for the day of the accident :</td>
			<td>'.$get_injured_data[0]->wages_payable.'</td>
		 </tr>
		 <tr>
			<td>10.</td>
			<td>Cause of accident :</td>
			<td></td>
		 </tr>';						
								
		if($get_all_data[0]->is_machinery_accident == 'Yes')
		{
			$output .= '<tr>
							<td>&nbsp;</td>
							<td>(a) If caused by machinery :</td>
							<td width="40%" valign="top"></td>
						 </tr>
						 <tr>
							<td>&nbsp;</td>
							<td style="padding-left: 15px;">(i) Give name of the machine and the part causing the accident</td>
							<td>'.$get_all_data[0]->machine_name.'</td>
						 </tr>
						 <tr>
							<td>&nbsp;</td>
							<td style="padding-left: 15px;">(ii) State whether it was moved by mechanical power at that time</td>
							<td>'.$get_all_data[0]->is_machinery_accident.'</td>
						 </tr>';
		} else {
			
			$output .= '<tr>
							<td>&nbsp;</td>
							<td>(a) If caused by machinery :</td>
							<td>'.$get_all_data[0]->is_machinery_accident.'</td>
						 </tr>';
		}
		
	$output .= '<tr>
				 	<td>&nbsp;</td>
					<td>(b) State exactly what the injured person was doing at that time :</td>
					<td>'.$get_injured_data[0]->accident_person_activity.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(c) In your opinion, was the injured person at the time of accident :</td>
					<td></td>
				 </tr>';
	
	$your_opnion_1 = ($get_injured_data[0]->your_opnion == 0) ? 'Yes' : 'No';
	$your_opnion_2 = ($get_injured_data[0]->your_opnion == 1) ? 'Yes' : 'No';
	
	$output .= '<tr>
				 	<td>&nbsp;</td>
					<td style="padding-left: 15px;">(i) acting in contravention of provisions of any law applicable to him</td>
					<td>'.$your_opnion_1.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td style="padding-left: 15px;">(ii) acting in contravention of any orders given by or on behalf of his employer</td>
					<td>'.$your_opnion_2.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(d) In case reply to (c) (i), (ii) or (iii) is in (he affirmative state whether the act was done for the purpose of and in connection with the employer s trade or business :</td>
					<td>'.$get_injured_data[0]->state_act_done.'</td>
				 </tr>
				 <tr>
				 	<td>11.</td>
					<td>In case the accident happened while travelling in the employers transport, state whether </td>
					<td></td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(i). The injured person was travelling as a passenger to or from his place work </td>
					<td>'.$get_injured_data[0]->is_travelling_for_work.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(ii). The injured person was travelling with the express or implied permission of his employer </td>
					<td>'.$get_injured_data[0]->is_travelling_express_impiled.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(iii). The transport is being operated by/on behalf of the employer/some other person by whom it is provided in pursuance of arrangements made with the employer </td>
					<td>'.$get_injured_data[0]->is_transport_provided.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(iv). The vehicle was being/not being operated in the ordinary course of public transport vehicle </td>
					<td>'.$get_injured_data[0]->is_course_of_transport_provided.'</td>
				 </tr>
				 <tr>
				 	<td>12.</td>
					<td>In case the accident happened while meeting mergency, state</td>
					<td></td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(i). Its nature</td>
					<td>'.$get_injured_data[0]->accident.'</td>
				 </tr>
				 <tr>
				 	<td>&nbsp;</td>
					<td>(ii). Whether the injured person at the time of accident was employed for the purpose of his employers trade/business in/about the permises at which the accident took place</td>
					<td>'.$get_injured_data[0]->accident_person_employed.'</td>
				 </tr>
				 <tr>
				 	<td>13.</td>
					<td>State how the accident occured</td>
					<td>'.$get_all_data[0]->accident_description.'</td>
				 </tr>
				 
				 	<tr><td colspan="3">&nbsp;</td></tr>
					<tr>
						<td>14.</td>
						<td colspan="2"><b>Name and Address of the witness :</b></td>
					</tr>';
				 
			$i = 0;
			while($i < count($get_witness_data))
			{ 
				$j = $i+1;
				$output .= '<tr>
								<td>&nbsp;</td>
								<td>'.$get_witness_data[$i]->witness_name.'</td>
								<td>'.$get_witness_data[$i]->witness_address.'</td>
							</tr>';
				$i++;			 
			}
			
		$output .= '<tr>
						<td width="7%" valign="top">15.</td>
						<td width="43%" valign="top">(a). Nature and extent of injury (e.g. fatal, loss of finger, fracture of leg, scale of scratch and followed by sepsis)</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->nature_of_injury.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">&nbsp;</td>
						<td width="43%" valign="top">(b). Location of injury (right leg, left hand or left eye etc.)</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->location_of_injury.'</td>
					 </tr>';
		
		if($get_injured_data[0]->fatal_accident == 'Yes')
		{			 
			$output .= '<tr> 
							<td width="7%" valign="top">16.</td>
							<td width="43%" valign="top">(a). If the accident is not fatal, state whether the injured person was disabled for 48 hours or more</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->disabled_48hrs.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(b). Date and hour of return to work</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->return_to_work_date.' at '.$get_injured_data[0]->return_to_work_time.'</td>
						 </tr>';
		} else {
			$output .= '<tr> 
							<td width="7%" valign="top">16.</td>
							<td width="43%" valign="top">(a). If the accident is not fatal, state whether the injured person was disabled for 48 hours or more</td>
							<td width="40%" valign="top">Non-fatal accident</td>
						 </tr>';
		}
		
		$output .= '<tr>
						<td width="7%" valign="top">17.</td>
						<td width="43%" valign="top">(a). Physician, dispensary or hospital from whom or in which the injured person received or is receiving treatment  </td>
						<td width="40%" valign="top">'.$get_injured_data[0]->treatment_location.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">&nbsp;</td>
						<td width="43%" valign="top">(b). Name of dispensary/panel doctor selected by the injured person </td>
						<td width="40%" valign="top">'.$get_injured_data[0]->doctor_name.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">18.</td>
						<td width="43%" valign="top">(i). Has the injured person died</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->is_accident_person_died.'</td>
					 </tr>';
		
		if($get_injured_data[0]->is_accident_person_died == 'Yes')
		{
			$output .= '<tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(ii) Date of death</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->date_of_death.'</td>
						 </tr>';
		}
				
	$output .= '</table></div></div></div>';
	
	$form = array();
	
	$form['application_documents'] = array(
		'#type' 			=> 'fieldset',
		//'#title' 			=> t('Application Preview'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
		'#markup' 			=> t($output),
	);
	$form['formid_hidden'] 		= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $formid
	);	
	$form['referenceid_hidden'] = array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $referenceid
	);	
	$form['factoryid_hidden'] 	= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $factoryid
	);	
	$form['application_documents']['output'] = array(
		'#markup' 			=> t($output),
	);
	
	if($get_all_data[0]->notice_status == 'RC')
	{
		 $form['application_forward'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Necessary action to be taken:'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE // Added
		 );
		 
		$accidentTypeOption= array('major' =>'Major','minor' =>'Minor');

		$form['application_forward']['accident_type_final'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="box box-info"><div class="box-header with-border"><div class="col-md-4 col-xs-12">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> 'Type of Accident',
			'#type' 			=> 'radios',
			'#options' 			=> $accidentTypeOption,
			 '#ajax'			=> array(
							 'event' 		=> 'change',
							 'effect' 		=> 'fade',			
							 'callback'		=> 'get_ajax_type_accident',
							 'progress'		=>	array(
							 'type'			=> 'throbber',
							 'message'		=> t('loading'),
						 )
			),
			'#required' 		=> TRUE,
		);


	  $value_type	= !empty($form_state['values']['accident_type_final'])? $form_state['values']['accident_type_final'] : '';

		if($value_type == 'major')
		{
			
			$users_action= array(	
				'DC'				=>'Forward to Dy CIF'
			);
			$form['application_forward']['forward_user'] 	= array(
				'#prefix' 			=> '<div id="forward_user_div"><div class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> 'Forward to',
				'#type' 			=> 'select',
				'#options' 			=> $users_action,
				'#default_value' 	=> $value_app,
				'#required' 		=> TRUE,
			);

		} else {
			
			$users_action= array(	
				'SC'				=>'Forward to Statistic Cell',
			);
			$form['application_forward']['forward_user'] 	= array(
				'#prefix' 			=> '<div id="forward_user_div"><div class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> 'Forward to',
				'#type' 			=> 'select',
				'#options' 			=> $users_action,
				'#default_value' 	=> $value_app,
				'#required' 		=> TRUE,
			);
		}

		$form['application_forward']['remarks'] 	= array(
			'#prefix' 			=> '<div class="col-md-8 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'textarea',
			'#default_value' 	=> '',
			'#required' 		=> TRUE,
		);
		$form['application_forward']['submit'] = array (
			'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div></div></div>',
			'#type' 			=> 'submit',
			'#attributes' 	    => array('class' => array('btn btn-info pull-right')),
			'#value' 		    => 'Continue'										  
		);
	}
	return $form;
 }
 
 function receiving_form18_view_submit($form, &$form_state){
		
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid          = $user->uid;
		$uname        = get_name($uid);
		$user_role    = array_keys($user->roles);
		$urole        = $user_role[1];
		
		$val   		  = $form_state['values'];

		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factoryid    = encryption_decryption_fun('decrypt', $val['factoryid_hidden']);
			
		$queryapp 	  =	db_update('fa_form18_notice_accident');
		$queryapp	 ->	fields(array('notice_status'=> $val['forward_user'],'accident_type_final'=> $val['accident_type_final']));
		$queryapp	 ->	condition('id',$formid,'=');
		$queryapp	 ->	condition('reference_number',$referenceid,'=');
		$queryapp	 ->	condition('factory_id',$factoryid,'=');
		$queryapp	 ->	execute();
			
		$notice_remarks = array(
			'notice_id'   			 => $formid,
			'remark_by_uid' 	     => $uid,
			'remark_by_roleid' 	     => $urole,
			'remark_by_name' 	     => $uname,
			'sending_time' 		     => date('Y-m-d h:i:s'),
			'notice_status' 		 => $val['forward_user'],
			'remarks' 	         	 => $val['remarks'],
			//'verify_details'	     => '',
			//'remark_to_user'	     => '',
			'notice_reference_no' 	 => $referenceid,							
			);
			
		db_insert('fa_notice_remarks')->fields($notice_remarks)->execute();
	
		drupal_goto('receiving-form18-list');

		$form_state['rebuild'] = true;
	} 
	
 function get_ajax_type_accident($form, $form_state){
	  
	  $commands = array();
	  $commands[] = ajax_command_replace('#forward_user_div', drupal_render($form['application_forward']['forward_user']));
	  return array('#type' => 'ajax', '#commands' => $commands);
  }  
	