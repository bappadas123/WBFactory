<?php
function display_notesheet($note_id,$ajax) {
	 if ($ajax) {
     // Required includes for ctools to work:
    ctools_include('ajax');
    ctools_include('modal');
	ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t(''),
	   'note_id' => encryption_decryption_fun('decrypt',$note_id),
     );
	 
	 $output = ctools_modal_form_wrapper('view_notesheet_details', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_notesheet_details');
   }
}

function view_notesheet_details($form, &$form_state) {	

		global $base_root,$base_path,$user;		
	
	$note_details =  get_notesheet_data_details($form_state['note_id']);
	//print_r($note_details);die;
	foreach($note_details as $data){
		$application_id 	= $data->application_no;
		$service_id 		= $data->service_id;
		$factory_type_id 	= $data->factory_type_id;
		$reference_no 		= $data->referance_no;
		$get_fa_cafa		= get_fa_cafa($application_id);
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
				$dates = explode(',', $data->dates);
				if(!empty($data->close_reg_no)){$close_reg_no= $data->close_reg_no;}else{$close_reg_no ="Nil";}
				if(!empty($data->date_restart)){$date_restart= date('dS M Y', strtotime($data->date_restart));}else{$date_restart ="Nil";} 
				if(!empty($data->date_cossed)){$date_cossed= date('dS M Y', strtotime($data->date_cossed));}else{$date_cossed ="Nil";} 
				if(!empty($data->date_shift_amenability)){$date_shift_amenability= date('dS M Y', strtotime($data->date_shift_amenability));}else{$date_shift_amenability ="Nil";}
				 
				
	$content .= '<table border="0" width="100%" cellspacing="0" cellpadding="0">
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">1. </td>
						<td width="15%"  align="left" valign="top" style="font-size:12px;">Date/Dates of Visit: </td>
						<td width="80%" align="left" valign="top" style="font-size:12px;">'; foreach($dates as $date){ 
						$content .= '<b>'. date('dS M Y', strtotime($date)).',&nbsp;</b>';
						}
		$content .= '</td>
					</tr>
					
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">2. </td>
						<td width="98%"  align="left" valign="top" style="font-size:12px;" colspan="3">In case of new or existing factory coming under the purview of the Act: </td>
					</tr>
					
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
						<td width="38%" align="left" valign="top" style="font-size:12px;">(a) Date of starting: <b>'.date('dS M Y', strtotime($data->factory_starting)).'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(b) Date of Amenability: <b>'.date('dS M Y', strtotime($data->factory_amenabity_date)).'</b></td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">3. </td>
						<td width="98%"  align="left" valign="top" style="font-size:12px;" colspan="3">In case of an old registered factory crossed/closed down /shifted- : </td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="38%" align="left" valign="top" style="font-size:12px;">(a) Registn No.: <b>'.$close_reg_no.'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(b) Date of Restarting: <b>'.$date_restart.'</b></td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="38%" align="left" valign="top" style="font-size:12px;">(c) Date of crossed off/ Closed down / shifting: <b>'.$date_cossed.'</b></td>
						<td width="40%" align="left" valign="top" style="font-size:12px;">(d) Date of Amenability: <b>'.$date_shift_amenability.'</b></td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">4. </td>
						<td width="38%"  style="font-size:12px;" colspan="3">Comments on information furnished relating to owner and occupier of promises / Factory: </td>
					</tr>
					<tr>
						<td width="2%"   valign="top" style="font-size:12px;"></td>
						<td width="38%"   valign="top" style="font-size:12px;">Name: </td>
						<td width="40%"  style="font-size:12px;"><b>'.$get_fa_cafa['owner_name'].'</b></td>
					</tr>
					<tr>
						<td width="2%"   valign="top" style="font-size:12px;"></td>
						<td width="38%"   valign="top" style="font-size:12px;">Comment: </td>
						<td width="40%"  style="font-size:12px;"><b>'.$data->owner_comment.'</b></td>
					</tr>
					<tr>
						<td width="2%"  align="left" valign="top" style="font-size:12px;">5. </td>
						<td width="98%"  align="left" style="font-size:12px;" colspan="3">Name / Names of major products in order of volume of production: </td>
					</tr>
					<tr>
										<th width="2%"  align="left" valign="top" style="font-size:12px;"></th>
										<th width="38%" align="left" valign="top" style="font-size:12px;">Sl.</th>
										<th width="40%" align="left" valign="top" style="font-size:12px;">Nature of manufacturing process</th>
									</tr>
					';
					$get_manufacturing = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
					//print_r($get_manufacturing);die();
					if($data->hazardous_product=='Y'){$check = 'YES';}else{$check= 'NO';}
					$i=1;
					foreach($get_manufacturing as $lst){
						$content .=	'
									<tr>
										<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
										<td width="38%" align="left" valign="top" style="font-size:12px;">'.$i.'</td>
										<td width="40%" align="left" style="font-size:12px;" >'.$lst->nature_manufacturing.'</td>
									</tr>';
					$i++;
					}
			$content .= '<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">6.</td>
							<td width="98%"  align="left" style="font-size:12px;" colspan="3">Nature and amount of installed power(KW/HP): <u><b>'.$data->power_install.'</b></u></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">7.</td>
							<td width="98%" align="left" style="font-size:12px;" colspan="3">(a) Maximum No. of workers employed on any day during the years preceeding the year of registration:  <u><b>'.$data->worker.'</b></u></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px;" colspan="3">(b) Number of workers on date of amenability: <u><b>'.$data->worker_at_amen.'</b></u></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">8.</td>
							<td width="98%" align="left" style="font-size:12px;" colspan="3">Approval No. <u><b>'.$data->approval_no.'</b></u> Date <u><b>'.$data->approval_no_date.'</b></u> of site and plans if approved, otherwise comments on confirmity of the site & building to be Act. </td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px;" colspan="3">Comment: <u><b>'.$data->plans_comment.'</b></u></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">9.</td>
							<td  width="98%" align="left" style="font-size:12px;" colspan="3">any other additional comment that the inspector may like to add relation to health hazards and safty, effluent disposal, approval of appropriate authority in respect of storage of inflammable liquids, gases etc. approval form environmental pollution department.</td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px; text-transform:uppercase;" colspan="3">Category &nbsp;&nbsp;<u><b>'.$data->category.'</b> </u>&nbsp;&nbsp; Reference Number &nbsp;&nbsp; <u>'.$data->category_ref.'</u>&nbsp;&nbsp; Approval date &nbsp;&nbsp; <u>'.date('dS M Y', strtotime($data->category_date)).'</u>
							</td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="98%" align="left" style="font-size:12px;" colspan="3">Comment: <u><b>'.$data->category_comment.'</b></u></td>
						</tr>
                        <tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">10.</td>
							<td width="98%" align="left" style="font-size:12px;"  colspan="3">Recommended for registration under classification <u><b>'.$data->classification.'</b></u>  category <u><b>'.$data->classification_category.'</b></u>  <u><b>'.$data->category_old_new.'</b></u>, w.e.f. <u><b>'.$data->amenability.'</b></u> as also grant and issue of licence after renewing if for upto H.P. <u><b>'.$data->hp.'</b></u> and worker upto <u><b>'.$data->worker_year.'</b></u> valid upto date <u><b>'.$data->last_year.'</b></u>.</td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">11.</td>
							<td width="98%" align="left" style="font-size:12px;"colspan="3"> Manufacture any chemical product ? <b><u>'.$check.'</u></b></td>
						</tr>
						<tr>
							<td width="2%"  align="left" valign="top" style="font-size:12px;">12.</td>
							<td width="98%" align="left" style="font-size:12px;"colspan="3">E-note:- &nbsp;&nbsp;<b>'.$data->note.'</b></td>
						</tr>
				</table>';	
			}

$form['notesheet_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$content,
        '#suffix' => '</div>',
     );
	
	 
	return $form;	
}