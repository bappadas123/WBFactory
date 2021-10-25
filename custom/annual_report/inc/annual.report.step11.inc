<?php

function annual_report_step11( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	       $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	
	 
	
	      $step10_select_query = db_select('labour_factory_statcell_annual_report_t11', 'a');
       
        $step10_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step10_select_query->fields('a',array('case_pending_at_beginning','case_disposed_of_during','case_pending_at_end','special_studies','seminar_training_courses','other_activities'));
        $step10_select_query_result = $step10_select_query->execute(); 
		
		$result_step10=$step10_select_query_result->fetchAssoc();
		$case_pending_at_beginning=$result_step10['case_pending_at_beginning'];
        $case_disposed_of_during=$result_step10['case_disposed_of_during'];
        $case_pending_at_end=$result_step10['case_pending_at_end'];
        $special_studies=$result_step10['special_studies'];
		
		$seminar_training_courses=$result_step10['seminar_training_courses'];
		$other_activities=$result_step10['other_activities'];
	
	
	
		
	

		
      $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       $inspector_name=get_name($inspector_id);
	
	   $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
       $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));  
	
	
	// Part 4
		
	      $form['step11field'] = array(
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.' </b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
           $form['step11field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

		
     	
$form['step11field']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>11.Prosecution Details</b></div><div class="form-group row"><div class="col-sm-8" >', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 5,

		                '#title' =>"(a) No.of cases pending at the beginning of the year",

                  '#default_value' =>$case_pending_at_beginning
	   
	   
           );


               
    $form['step11field']['colD2'] = array
              (
		       '#prefix' => '<div class="col-sm-8" >', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"(b) No.of cases disposed of during the year -",
		        '#suffix'=>'</div>',
		         '#default_value' =>$case_disposed_of_during
	   
	   
	   
           ); 

      $form['step11field']['colD3'] = array
              (
		       '#prefix' => ' <div class="col-sm-8" >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"(C) No.of cases pending at the end of the year -",
		               '#default_value' =>$case_pending_at_end
	   
	   
           ); 


              
$form['step11field']['colD4'] = array
              (
		       '#prefix' => '<div class="col-sm-8" >', 
		         '#type' => 'textarea',
		           '#title' =>"12. Details of special studies conducted.",
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</div>',
		             '#default_value' =>$special_studies
	   
	   
           );
           $form['step11field']['colD5'] = array
              (
		       '#prefix' => '<div class="col-sm-8" >', 
		         '#type' => 'textarea',
		        '#title' =>"13. Details of seminar,training courses, etc conducted.",
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</div>',
		            '#default_value' =>$seminar_training_courses
	   
	   
           );

           
             
             
 $form['step11field']['colD6'] = array
              (
		       '#prefix' => '<div class="col-sm-8" >', 
		         '#type' => 'textarea',
		         '#title' =>"14. Details of other activities, worth mentioning.",
               
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</div></div>',
		             '#default_value' =>$other_activities
	   
	   
           );

              


			$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" class="col-sm-8">',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }


function annual_report_step11_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$colD1=trim($val['colD1']); if(!$colD1)  $colD1= NULL;   
	$colD2=trim($val['colD2']); if(!$colD2)  $colD2= NULL;   
	$colD3=trim($val['colD3']); if(!$colD3)  $colD3= NULL;   

	$colD4=trim($val['colD4']); 
    $colD5=trim($val['colD5']); 
    $colD6=trim($val['colD6']); 

     $txn = db_transaction();
	  try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_t11 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_t11');
      $query_update_B->fields(array(
		  'case_pending_at_beginning' =>$colD1, 'case_disposed_of_during' => $colD2, 'case_pending_at_end' => $colD3, 'special_studies' => $colD4, 'seminar_training_courses' => $colD5, 'other_activities' => $colD6 ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step11/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {




	  	 $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t11');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;

 $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'case_pending_at_beginning' =>$colD1, 'case_disposed_of_during' => $colD2, 'case_pending_at_end' => $colD3, 'special_studies' => $colD4, 'seminar_training_courses' => $colD5, 'other_activities' => $colD6);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t11')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step11/'.encryption_decryption_fun('encrypt',$inspectionid);
                    }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step11/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }

