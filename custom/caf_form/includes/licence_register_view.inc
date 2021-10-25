<?php

function licence_register_view($form, &$form_state,$id) {
	
	$id		= encryption_decryption_fun('decrypt',$id);

$form['licence_register_details']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Licence Register Details</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['licence_register_details']['markup'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_register($id),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
  	);	
	
	$reg_link	= l('Download Licence Register', 'licence-registration-download-file/'.encryption_decryption_fun('encrypt',$id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	
	$form['licence_register_details']['generate_licence_register'] = array(
			'#prefix' => '<div class="col-md-4 col-xs-4">'.$reg_link,
			'#suffix' => '</div>',
		);	
	
	
	$form['licence_register_details']['markup_end1'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	
	return $form;

}

function get_all_register($id){
	global $base_root,$base_path,$user;
	//die($id);
	$get_all_data =  get_licence_register($id);
	foreach($get_all_data  as $register){
	
	$content = '<style type="text/css">
					table, td, th {
							font-size:18px;
							height:15px;
							color:#000;
							margin-top:10px;
							background:#fff;
							
					}
					th {
						background-color: #008BD1;
						color: white;
					}
					td:hover {
						background-color:#d4e3e5;
					}
					h1 {
						font-size:18px;
						font-weight:normal;
					}
					h2,h3,h4 {
						font-size:18px;
						margin-left: 10px;
					}
					table, td, h2,h3,h4 {
						font-size:18px;
						margin-left: 10px;
					}
					#tabular {
						border-collapse: collapse;
						
						}
					#tabular td {
						border: 1px solid;
						padding: 2px;
					}
					#tabular tr {
						padding-top: 12px;
						padding-bottom: 12px;
						text-align: left;
						background-color: #666;
						color: white;
						}
					.data{ text-transform: uppercase;font-weight:bold;}
			</style>';
					
	$content .= '<table width="100%" cellspacing="0" cellpadding="5" style="border-bottom: 1px solid #000; border-top:0px solid #000;">
				 	<tr>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Classification No.&nbsp;</span>'.$register->classification_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Registration No.&nbsp;</span>'.$register->registration_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Date.&nbsp;</span>'.date('dS M Y', strtotime($registration_date)).'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Licence No.&nbsp;</span>'.$register->licence_no.'</td>
					</tr>
				</table>';
				
	$content .= '<table width="100%" cellspacing="0" border="1" cellpadding="0">
				 	<tr>
						<td align="left" style="font-size:12px;"><h2>Name & Address of the Factory </h2><span style="font-size:12px;font-weight:bold;margin-left: 10px;">'.$register->factory_name_address.'</span></td>
						<td align="left" style="font-size:12px;"><h2>Name of the Occupier</h2><span style="font-size:12px;font-weight:bold; margin-left: 10px;">'.$register->occupier_name.'</span></td>
					</tr>
					<tr>
						<td align="left" style="font-size:12px;"><h2>Change Name...</h2><span style="font-size:12px;font-weight:bold;margin-left: 10px;">'.$register->factory_name_address.'</span></td>
						<td align="left" style="font-size:12px;"><h2>Occupier transfer..</h2><span style="font-size:12px;font-weight:bold; margin-left: 10px;">'.$register->occupier_transfer.'</span></td>
					</tr>
				</table>';
				 
	$content .= '<table id="tabular">
				<tr>					 				
                 	<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Year </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" colspan="2"> Licence Issued for<br/>Category: <br/>Schedule: <br/> </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" rowspan="2"> Amount of fee paid<br/>(a) Registration fee<br/>(b) Licence fee<br/>(c)Amendent Fees<br/>(d)Transfer Fees<br/>(e)late Fees<br/>(f)Loss Fees</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Date of Deposit </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Serial no. Challan reg. </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount paid</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount adjusted</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Entered by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Checked by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Remarks</td>
				</tr>
				<tr>					 				
					<td width="10%" style="font-size:12px;" align="center" valign="top" > HP/KW </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top"> Worker </td>
				</tr>';
		 
	}	
	$register_list = get_licence_register_list($id);
			//print_r($register_list);die;
			foreach($register_list as $row){	
			$dates = explode(',', $row->deposit_date);
	$content .= '<tr>					 				
					<td width="10%"  style="font-size:12px;"align="center"> '.$row->licence_period.' </td>
					<td width="10%"  style="font-size:12px;"align="center"> '.$row->power.''.$row->power_type.' </td>
					<td width="10%"  style="font-size:12px;"align="center"> '.$row->worker.' </td>
					<td width="10%"  style="font-size:12px;"align="left">(a)'.$row->register_fee.'<br/>(b)'.$row->renewal_fee.'<br/>(c)'.$row->amendment_fee.'<br/>(d)'.$row->transfer_fee.'<br/>(e)'.$row->late_pay_fee.'<br/>(f)'.$row->loss_fee.' </td>
					<td width="10%"  style="font-size:12px;"align="center">';
					foreach($dates as $date){
		$content .= date('dS M Y', strtotime($date)).'<br/>';
					}
	    $content .= '</td>
					<td width="10%"  style="font-size:12px;"align="center"> '.$row->challan_no.'</td>
					<td width="10%"  style="font-size:12px;"align="center"> '.$row->excees_fees.'</td>
					<td width="10%"  style="font-size:12px;"align="center">'.$row->adjusted_fees.'</td>
					<td width="10%"  style="font-size:12px;"align="center">'.get_name($row->uid).'</td>
					<td width="10%"  style="font-size:12px;"align="center"></td>
					<td width="10%"  style="font-size:12px;"align="center">'.$row->register_remarks.'</td>
				</tr>';
			}
				
	$content .= '</table>';
	
	return  $content;

}

