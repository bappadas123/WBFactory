<?php
function court_inspection_infringement_details($form, &$form_state, $id=NULL,$infg_id=NULL ,$st_id=NULL){
	
	//print "sssssssssssssssssssss".$ii;
	//exit;
		 global $base_root, $base_path,$full_base;
		  $id=  trim($id);
		  
		 $infg_id= encryption_decryption_fun('decrypt', trim($infg_id));
		 
		  $st_id= encryption_decryption_fun('decrypt', trim($st_id));
		 



$form['inspefield'] = array(
          '#title' => t(''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );
		 
		  
		$options_finyear = labour_inspection_option();
	    $options_finyear =  array('select' => " select ") + $options_finyear ; 
	    $value_finyear = $id ? $id : key($options_finyear);
	  
	  // if(isset($form_state['values']['applicant_inspection'])){
		if($id)
	   {
		   
		$form['inspefield']['applicant_inspection'] = array(
	     '#prefix' => '<div  class="inf-insp-note-table">',
         '#suffix' => '</div>',
        '#type' => 'select',
        '#title'=>'Select  Act from dropdown for infringement details',
		'#required' => TRUE,
       
		
		'#options' => $options_finyear,
		'#default_value' =>$id,
		// '#attributes' => array('onchange' => 'this.form.submit(applicant_inspection);'),
		//'#submit' => array('INFG_SAVE_WITH_NO_INFRINGEMENT'),
			'#attributes' => array('onchange' => 'javascript:location.href = this.value'),
		
	);   
		   
	   }
	   else
	   {
		   
		$form['inspefield']['applicant_inspection'] = array(
	     '#prefix' => '<div  class="inf-insp-note-table">',
          '#suffix' => '</div>',
        '#type' => 'select',
        '#title'=>'Select  Act from dropdown for infringement details',
		'#required' => TRUE,
       
		
		'#options' => $options_finyear,
		'#default_value' =>$value_finyear,
		
		'#attributes' => array('onchange' => 'javascript:location.href = this.value'),
		//'#submit' => array('INFG_SAVE_WITH_NO_INFRINGEMENT'),
		 //'#attributes' => array('onchange' => 'this.form.submit(applicant_inspection);'),
		//'#submit' => array('INFG_SAVE_WITH_NO_INFRINGEMENT'),
		
	);   
	   }

 //  print "sssssssssssssss".$form_state['values']['applicant_inspection'];
		 //exit;
	   $drop_down_value_ins='';
   /* if(trim($form_state['values']['applicant_inspection'])){
		  $drop_down_value_ins=trim($form_state['values']['applicant_inspection']);
		//{
			//print $drop_down_value_ins;
			//exit;
			
		  $full_base=$base_root.$base_path.'court-inspection/'.$drop_down_value_ins;

		 // print  $full_base;
		// exit;
                           drupal_goto($full_base);
		}*/




	
		if(  trim($id) ){	
		  
		  
		$order='txt_order';
		$sort='ASC';
		$show_details_query = db_select('fa_inspection_master', 't');
	   
	   

        $show_details_query->fields('t', array('ispection_id','inspection_txt','inspection_type','txt_order','ins_rule','ins_section'));
		
		
	
  
    if( $drop_down_value_ins){	  
	
		// $show_details_query->condition('t.inspection_txt_type',  trim($infg_id) , '=');  
		
		$show_details_query->condition('t.inspection_type',  trim( $drop_down_value_ins) , '=');  
	  } 
	  elseif(trim($id))
	 //if(trim($id) && trim($infg_id))
	  
	  {
	  
	  
     $show_details_query->condition('t.inspection_type',  trim($id) , '=');
	 
	  }
   
    $show_details_query->orderBy($order, $sort);
   
 // $show_details_query = $show_details_query->extend('PagerDefault')->limit(50);
		
		
//print $app_user_query;
 $total_name =  $show_details_query->execute();
 
 
 $numrow=$total_name->rowCount(); 
	 }
	 print 'pppppp'.$id.'='.$numrow;
	 
if($numrow > 0  ){


 $form['inspefield']['insslno'] = array
        (
		  '#prefix' => '<table width="100%" class="inf-insp-note-table2"><tr><th width="7%">',
	        '#suffix' => '</th>',
			
		   '#markup'=>'SL.NO',
	   
	   
        );
 
 
 
 $form['inspefield']['pensionfc'] = array
        (
		    '#prefix' => '<th width="15%"><b>',
	        '#suffix' => '</b></th>',
		    '#type' => 'checkbox',
          '#title' => t('SELECT ALL'),
         
         '#value' =>0,
         
		  '#attributes' => array('onClick' => 'calpetxteqal('.$numrow.')'), 
	   
	    
        );

        $form['inspefield']['inssec'] = array
        (
		    '#prefix' => '<th>',
	        '#suffix' => '</th>',
		   '#markup'=>'SECTION',
	   
	   
        );
        $form['inspefield']['insrule'] = array
        (
		    '#prefix' => '<th>',
	        '#suffix' => '</th>',
		   '#markup'=>'RULE',
	   
	   
        );
	$form['inspefield']['insarea'] = array
        (
		    '#prefix' => '<th>',
	        '#suffix' => '</th></tr>',
		   '#markup'=>'INFRINGEMENTS',
	   
	   
        );
	
 $i=0;
        $ispection_id = ""; 
         $inspection_txt = "";
        $txt_order = "";
		$oddevn='';
	foreach ($total_name as $data) {
			$i++;
	     $ispection_id = $data->ispection_id; 
         $inspection_txt = $data->inspection_txt;

          $ins_rule = $data->ins_rule;
           $ins_section = $data->ins_section;
        $txt_order = $data->txt_order;
 
  if($i%2==0){
		        $bgcol = "#FCF6CF";
				 $oddevn='odd';
				 }
				else
				{
				$bgcol = "#FEFEF2";
				$oddevn='even';
				}	 
	
	
	$form['inspefield']['hiddinsid'.$i] = 
	    array('#type' => 'hidden',  
	    '#value' => $ispection_id,
	   
	   );
 $form['inspefield']['slno'.$i] = array
          (
		 '#prefix' => '<tr class="'.$oddevn.'"><td>',
	      '#suffix' => '</td>',
	    
		  '#markup'=>''. $i.'.'.'',
		
          );
 
		
		


		   $form['inspefield']['insid'.$i] = array
          (
		 '#prefix' => '<td >',
	      '#suffix' => '</td>',
	      '#type' => 'checkbox',
		//'#default_value' => $numinfg == '0' ? FALSE : TRUE,
	

          );

           $form['inspefield']['sec'.$i] = array
        (
		    '#prefix' => '<td  >',
	         '#suffix' =>  '</td>',
		   '#markup'=>'<b>'.$ins_section.'</b>',
		   
		    '#attributes' => array('class' => array('textarea-inf-note')),
		
		// '#type' => 'text_format',
		
	 
	   
	    // '#size'=>t('50'),	
	    // '#type' => 'textfield',
	     //'#value' =>trim($inspection_txt)
	   
	   
	 //  '#default_value' =>trim($inspection_txt)
        ); 

        $form['inspefield']['rule'.$i] = array
        (
		    '#prefix' => '<td  >',
	         '#suffix' =>  '</td>',
		   '#markup'=>'<b>'.$ins_rule.'</b>',
		   
		  //  '#attributes' => array('class' => array('textarea-inf-note')),
		
		// '#type' => 'text_format',
		
	 
	   
	    // '#size'=>t('50'),	
	    // '#type' => 'textfield',
	     //'#value' =>trim($inspection_txt)
	   
	   
	 //  '#default_value' =>trim($inspection_txt)
        );  

     $form['inspefield']['reprin'.$i] = array
        (
		    '#prefix' => '<td  >',
	         '#suffix' =>  '</td></tr>',
		//'#markup'=>'<b>'.$inspection_txt.'</b>',
		   
		    '#attributes' => array('class' => array('textarea-inf-note')),
		
		// '#type' => 'text_format',
		 '#type' => 'textarea',
		'#cols' => 30, 
        '#rows' => 2,    
		   
	 
	   
	    // '#size'=>t('50'),	
	    // '#type' => 'textfield',
	     //'#value' =>trim($inspection_txt)
	   
	   
	   '#default_value' =>trim($inspection_txt)
        );     
}
	$form['inspefield']['typeinfrg'] = 
	    array('#type' => 'hidden',  
	   // '#value' => trim($form_state['values']['applicant_inspection']),
	   //'#value' => (!empty($infg_id)) ? $infg_id : trim($form_state['values']['applicant_inspection']),
	   
	    '#value' => (!empty($drop_down_value_ins)) ? $drop_down_value_ins : trim($id),
	   );

	$form['inspefield']['submit1'] = array (
		  '#prefix' => '<tr ><td  >',
	      '#suffix' => '</td>',
         '#type' => 'submit',
         '#submit' => array('INFG_SAVE_WITH_INFRINGEMENT'),
      
     
       
        //'#executes_submit_callback' =>!empty(trim($form_state['values']['applicant_inspection'])) ?  TRUE : FALSE,
        '#value' => 'Save',
        //'#attributes' => array('onclick' => 'return (true);'),
        //'#element_validate' => array('INFG_CHECKING_validate'),
	  
        );

	$form['inspefield']['submit2'] = array (
		  '#prefix' => '<td  >',
	      '#suffix' => '</td>',
          '#type' => 'submit',
         '#submit' => array('INFG_SAVE_WITH_NO_INFRINGEMENT'),
     
       // '#executes_submit_callback' => !empty(trim($form_state['values']['applicant_inspection'])) ?  TRUE : FALSE,
        '#value' => 'Save with no infringements',
       
       // '#element_validate' => array('INFG_CHECKING_validate'),
	    // '#description' =>  t('If no infringements detected/full compliance then just leave all the checkbox blank and save'),
	    //'#title' =>t('If no infringements detected/full compliance then just leave all the checkbox blank and delete additional infringements if any and save'),
        );
 $form['inspefield']['resetinfg'] = array(
		                                               // '#markup'=>$link_reset,
														 '#prefix' => '<td  >',
														 '#suffix' => '</td></tr></table>',
	                                                      ); 
}
         return $form;
 }
 function court_inspection_infringement_details_submit($form, &$form_state) {
	 
	 

         $val=$form_state['values'];
//return true;
        //$form_state['rebuild'] = TRUE;
		  $typeinfrg=trim($val['applicant_inspection']);
		// print "mmmm";
		// exit;
                          
				            global $base_root, $base_path,$full_base;
					    
				          $full_base=$base_root.$base_path.'court-inspection/'.$typeinfrg;
                            drupal_goto($full_base);

		}
function INFG_SAVE_WITH_NO_INFRINGEMENT($element,&$form_states)
{
	//return true;
print 'nnnnn';
exit;
}
function INFG_SAVE_WITH_INFRINGEMENT($element,&$form_states)
{
	//return true;
print 'yyyyy';
exit;
}
 function labour_inspection_option() {
global $base_root, $base_path,$full_base;
   $finyear_query=db_query("SELECT inspection_type, inspection_type_name FROM {fa_inspection_master} group by inspection_type,inspection_type_name order by inspection_type desc"); 	
	
	 foreach ($finyear_query as $result)
     {
      	$res[$base_root.$base_path.'court-inspection/'.$result->inspection_type]=$result->inspection_type_name;      	
     }
	
     return $res;
	
	
	
  }
 ?>