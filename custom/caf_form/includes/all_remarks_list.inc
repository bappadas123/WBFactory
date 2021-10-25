<?php

function all_remarks($application_id,$referance_no,$ajax) {	
	 if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
	ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t(''),
	   'app_id' => encryption_decryption_fun('decrypt',$application_id),
	   'ref_no' => encryption_decryption_fun('decrypt',$referance_no),
     );
	 
	 $output = ctools_modal_form_wrapper('view_remarks', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_remarks');
   }
}
   
function view_remarks($form, &$form_state) {	

	$query_note		= 	db_select('fa_cafa_remarks', 'rm');
	$query_note     ->  InnerJoin('role', 'r', 'rm.remark_by_roleid=r.rid');
	$query_note     ->  InnerJoin('users', 'u', 'rm.remark_by_uid=u.uid');
	$query_note		->	fields('rm',array('id','sending_time','remarks','remark_by_name','remark_by_roleid','remark_by_uid','status'));
	$query_note		->	fields('r',array('name'));
	$query_note		->	fields('u',array('name'));
	$query_note		-> 	condition('rm.app_id', $form_state['app_id']);
	$query_note		-> 	condition('rm.app_reference_no', $form_state['ref_no']);
	$query_note		-> 	condition('rm.remark_type', 'r');
	$query_note		-> 	condition('rm.remarks',' ','!=');
	$query_note		->	orderBy('rm.id','ASC');
	$result_note	= $query_note->execute()->fetchAll();

	
	$output = '<table class="table pretty table-bordered table-hover">
	  <tr align="center">
		<th>Sl No.</th>
		<th>Name</th>
		<th>Remarks</th>
		<th>Date</th>
	  </tr>';
	 if(!empty($result_note))
	 {
		for ($i = 0 ; $i < count($result_note); $i++){
			$j = $i+1;
			
		$date = date_create($result_note[$i]->sending_time); //die;
		$send_date = date_format($date,'F j, Y');
		if(!empty($result_note[$i]->remark_by_roleid)){
			
			$design = get_role_name($result_note[$i]->remark_by_roleid);
			if($design == 'regsection'){$designation='Designation:- Reg. Section';}
			elseif($design == 'applicant'){$designation='Applicant';}
			elseif($design == 'factoryinspector'){$designation='Designation:- Assistance Director';}
			elseif($design == 'deputychief'){$designation='Designation:- Deputy Director';}
			elseif($design == 'jointchief'){$designation='Designation:- Joint Director';}
			elseif($design == 'chief'){$designation='Designation:- Director';}
			$show = ' ( '.$designation.')';
			}else{$show = '';}
			if(!empty(get_name($result_note[$i]->remark_by_uid))){
				$name=	get_name($result_note[$i]->remark_by_uid);
			}else{
				$name=	get_applicant_name($result_note[$i]->remark_by_uid);
			}
		$output .= '<tr align="left">
						<td>'.$j.'</td>
						<td>'.$name.'&nbsp;'.$show.'</td>
						<td>'.$result_note[$i]->remarks.'</td>
						<td>'.$send_date.'</td>
					</tr>';
		}
	}
	 else{ 
	 	$output .= '<tr align="center"><td colspan="5">No Data Found</td></tr>';
	  }
	  
	$output .= '</table>';
	
	$form['view_remarks']['show_remarks_div'] = array(
	   '#prefix' => '<div>'.$output,
        '#suffix' => '</div>',
     );
	 
	return $form;	
}
