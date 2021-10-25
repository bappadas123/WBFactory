
<?php

function monthly_report_list( $form, &$form_state , $filenumber= NULL  ){
	
	
	 global $base_root, $base_path , $user;
	 
	 $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	 
	   $uid	=	$user->uid; 

	   //print "sssssssssssssss".$uid;

	   // $roleId=get_role_id($uid);
           
             //$role_name=get_role_name($roleId);

            // print $role_name;


     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');	
	 
   
//$thisYear = date("Y")-1;
              $form['monthlyreportfield'] = array(
          '#title' => t(' Monthly Report'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
   $form['monthlyreportfield']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );

	  $form['monthlyreportfield']['monthly_report_id'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );

	    $report_from_date=NULL;
       $report_to_date=NULL;

       $area=NULL;
       $area_id=NULL;

       if(trim($filenumber)){

        $mr_elevenquery = db_select('labour_factory_statcell_form_5', 'a');
       
        $mr_elevenquery->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $mr_elevenquery->fields('a',array('area','report_to_date','report_from_date','area_id'));
        $mr_elevenquery_result = $mr_elevenquery->execute(); 
    
       $result_elevenq=$mr_elevenquery_result->fetchAssoc();
       $report_from_date=$result_elevenq['report_from_date'];
       $report_to_date=$result_elevenq['report_to_date'];

       $area=$result_elevenq['area'];
       $area_id=$result_elevenq['area_id'];

        }


            $form['monthlyreportfield']['from'] = array
              (
		      
		      
		    '#title' => t('From: '),
           

               '#type' => 'textfield',
                '#size' => 12,
                 '#attributes' => array('class' => array('datepicker_retify') ,  'autocomplete' => 'off'),
	       

		     
		     // '#attributes' => array('readonly' => 'readonly'),
	           '#required' => TRUE,
	           '#prefix' => '<div class="form-group row"><div class="col-sm-4"> <i class="fa fa-calendar"></i>', 
   
		       '#suffix'=>'</div>',

		      
		      '#default_value' => !empty($report_from_date) ? date('d-m-Y', strtotime($report_from_date)) : NULL , 
	   
           ); 

           $form['monthlyreportfield']['to'] = array
              (
		  
		     
		    '#title' => t('To: '),
            

             '#type' => 'textfield',
                '#size' => 12,
                 '#attributes' => array('class' => array('datepicker_retify') , 'autocomplete' => 'off'),
	       
	  
	        '#required' => TRUE,
		  
		    '#prefix' => '<div class="col-sm-4"> <i class="fa fa-calendar"></i>', 
   
		       '#suffix'=>'</div>',
		    
		    '#default_value' => !empty($report_to_date) ? date('d-m-Y', strtotime($report_to_date)) : NULL , 
		        
	   
	   
           ); 

            $user_zone=explode(",",$area_id)  ;

        $options_zone = array(0 => " Select  ") + anr_zone_option();
       // if(in_array($options_zone, $user_zone))
         
          $form['monthlyreportfield']['anr_zone'] = array (
                    '#type' => 'select',
                    '#title' => ('Zone'),
				    '#options' 		 => $options_zone,
				     

				     '#default_value' => array_values($user_zone) ,  
			    	
		            '#required' => TRUE,
					 '#multiple'     =>  true,
					  '#attributes' => array('style' => array('height: 100px;')),
				
	              '#prefix' => '<div class="col-sm-4">', 
   
		          '#suffix'=>'</div>',
	                '#rows'        => 10,

               );
	   
	   
	    if(trim($filenumber)){

	   	$form['monthlyreportfield']['submit_button']	= array(
																 
                                                              

                                                                '#prefix' => '<div style="text-align:right;" class="col-sm-12" >',
                                                                 '#suffix'=>'</div></div>',


																'#type'					=>'submit',
																'#value'				=>t(' Update & Next '),
																'#element_validate' => array('monthly_report_edit_validate'),
																); 	

	    }
	    else
	    {
	   
          	$form['monthlyreportfield']['submit_button']	= array(
																 
                                                                '#prefix' => '<div style="text-align:right;" class="col-sm-12">',
                                                                 '#suffix'=>'</div></div>',
																'#type'					=>'submit',
																'#value'				=>t(' Next '),
																'#element_validate' => array('monthly_report_validate'),
																);
		 
	   }
	  
		 
	 $rows = array();
    $header = array();

    	$header = array(
          array('data'=> 'SL.NO', 'class' => array('')),
          array('data' => ' MONTH',   'class' => array('')),
		  array('data' => ' YEAR',   'class' => array('')),
		  array('data'=> 'From - To', 'class' => array('')),
          array('data' => 'Area', 'class' => array('')),
          array('data' => 'Status', 'class' => array('')),
		  array('data' => 'EDIT/PRINT', 'class' => array('')),
		 
		 
		 
		 
	);	

	$sort = 'DESC';
	$order = 'monthly_form_id';
	$monthly_list_query = db_select('labour_factory_statcell_form_5', 't');
	
	
	
	$monthly_list_query->fields('t',array('monthly_form_id','report_month','report_year','report_from_date',
	'report_to_date','area','inspector_id','appeal_to_high_court','other_mat_special_interest','last_updated','is_submitted','create_by','status'));
	$monthly_list_query->condition('t.inspector_id',trim($uid),'=');
	
	$monthly_list_query = $monthly_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
	$monthly_list_query->orderBy($order, $sort);
	$monthly_list_query_result = $monthly_list_query->execute();
	
	//print $ins_list_query;
	$i=0;
	foreach($monthly_list_query_result as $data){
		$i++;
		$mr_status='';
          /* if(trim($data->is_submitted) && trim($data->status)=='FD'){
		   
		   $mr_status='Forward to Deputy chief';
          
		    $kk=$base_root.$base_path.'admin/monthly-report-print/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}
		elseif(trim($data->is_submitted) && trim($data->status)=='BI')
		{
          $mr_status='Back to inspector';
            $kk=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		    $link_create_annual_report=l(t('<font color="DarkGreen"><b>EDIT</b></font></br>'), $kk,array('html'=>TRUE)) ;

		}
		elseif(trim($data->is_submitted) && trim($data->status)=='RS'){
		   
		   $mr_status='resubmit to Deputy chief';
          
		    $kk=$base_root.$base_path.'admin/monthly-report-print/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}*/
		if(trim($data->is_submitted) && trim($data->status)=='FS'){
		   
		   $mr_status='Forward to Statistical Unit';
          
		    $kk=$base_root.$base_path.'admin/monthly-report-print/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}
		elseif(!trim($data->is_submitted)  && trim($data->status) =='I' )
		{
			$mr_status='Incomplete';
            $kk=$base_root.$base_path.'admin/monthly-report-list/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		    $link_create_annual_report=l(t('<font color="DarkGreen"><b>EDIT</b></font></br>'), $kk,array('html'=>TRUE)) ;

		}

	$rows[] = array(
      				
					$i,
					date("F", mktime(0, 0, 0, $data->report_month, 10)) ,
					$data->report_year,
					
					
					date('d/m/Y', strtotime($data->report_from_date)).'-'.date('d/m/Y', strtotime($data->report_to_date)),
					
					$data->area,
					$mr_status,
					$link_create_annual_report,
					
					
					
				);


}
				$variables = array(
	  			  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
	  			'header' 			=> $header,
	  			'rows'				=> $rows,
		);
		$output = theme('table', $variables).theme("pager");
	     $form['monthlyreportfield']['addshowprin'] = array(
					'#markup'=>$output,
					); 
	
		

	   
	
	   
       return $form; 
  }

  function monthly_report_validate($element,&$form_state)
  {
  
    $val=$form_state['values'];
    $uid=trim($val['uid']);

	$monthly_report_id=trim($val['monthly_report_id']);
	
	
	$from=trim($val['from']);
	$from_brk = explode("-", $from);
	$from_date=$from_brk[2]."-".$from_brk[1]."-".$from_brk[0];

	$to=trim($val['to']);

	$to_brk = explode("-", $to);
	$to_date=$to_brk[2]."-".$to_brk[1]."-".$to_brk[0];
    //print $uid.'='.$from.'='.$to;
    //exit;
    
   
     $mon_report=db_query('select  * from labour_factory_statcell_form_5 where  inspector_id=:insid and report_month=:rm and report_year=:ry', array(':insid' => $uid , ':rm' => $from_brk[1] , ':ry' => $from_brk[2] ));

        if((strtotime($from_date) > strtotime($to_date)) || ( strtotime($from_date) == strtotime($to_date))){

          form_error($element, t(' To date is always greater than the From date   . '));

        }
        elseif($from_brk[1] != $to_brk[1]){

          form_error($element, t(' From date  and To date is  not equal month  . '));

        }

        elseif($from_brk[2] != $to_brk[2]){

          form_error($element, t(' From year  and To year is  not equal   . '));

        }
		
	    elseif($mon_report->rowCount() > 0) 
          { 
	  
	 
	     form_error($element, t(' monthly  report already exist this month . '));
	 
		 
	   
          
		 }
}


 function monthly_report_edit_validate($element,&$form_state)
  {
  
    $val=$form_state['values'];
    $uid=trim($val['uid']);

	$monthly_report_id=trim($val['monthly_report_id']);
	
	
	$from=trim($val['from']);
	$from_brk = explode("-", $from);
	$from_date=$from_brk[2]."-".$from_brk[1]."-".$from_brk[0];

	$to=trim($val['to']);

	$to_brk = explode("-", $to);
	$to_date=$to_brk[2]."-".$to_brk[1]."-".$to_brk[0];
    //print $uid.'='.$from.'='.$to;
    //exit;
    
   
    // $mon_report=db_query('select  * from labour_factory_statcell_form_5 where  inspector_id=:insid and report_month=:rm and report_year=:ry', array(':insid' => $uid , ':rm' => $from_brk[1] , ':ry' => $from_brk[2] ));

        if((strtotime($from_date) > strtotime($to_date)) || ( strtotime($from_date) == strtotime($to_date))){

          form_error($element, t(' To date is always greater than the From date  . '));

        }
        elseif($from_brk[1] != $to_brk[1]){

          form_error($element, t(' From date  and To date is  not equal month  . '));

        }
        elseif($from_brk[2] != $to_brk[2]){

          form_error($element, t(' From year  and To year is  not equal   . '));

        }
		
	   /* elseif($mon_report->rowCount() > 0) 
          { 
	  
	 
	     form_error($element, t(' monthly  report already exist this month . '));
	 
		 
	   
          
		 }*/
}

function anr_zone_option() {
	$blk="SELECT * FROM {fa_zone} ORDER BY zone_id";
	
    $state_query=db_query($blk);

  $options 				= array();
	
	foreach($state_query as $state_result) {
		
		$options[$state_result->zone_id] =$state_result->zone_name;	 
	
	}
	
	
	
   
       return $options;
		
  
      
	
	
}

function monthly_report_list_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);
//exit;


  
	$uid=trim($val['uid']);

	$monthly_report_id=trim($val['monthly_report_id']);
	
	
	$from=trim($val['from']);
	$from_brk = explode("-", $from);
	$from_date=$from_brk[2]."-".$from_brk[1]."-".$from_brk[0];

	$to=trim($val['to']);

	$to_brk = explode("-", $to);
	$to_date=$to_brk[2]."-".$to_brk[1]."-".$to_brk[0];
	


    //print $from_date."-".$to_date;
   // exit;
	

	$zone = array_filter($form_state['values']['anr_zone']);
	//print $zone;
	//exit;

 $txn = db_transaction();
	  try {

           if($monthly_report_id){


      $area=NULL;
      $area_id=NULL;
		     $i=1;
           foreach( $zone as $a){
	       $query_zone=db_query('select  *  from fa_zone where  zone_id = :znid', array(':znid' => trim($a) ));

	        $result_zone=$query_zone->fetchAssoc();
		    
			
  
	           if($i > 1){
               $area.=","; 
               $area_id.=","; 
               }  
	           $area.=trim($result_zone['zone_name']);
	           $area_id.=trim($result_zone['zone_id']);
	           $i++;
	        
		  }


       $query_update_A = db_update('labour_factory_statcell_form_5');
      $query_update_A->fields(array(
      'report_from_date' =>$from_date, 'report_to_date' => $to_date ,'area' =>$area ,'area_id' => $area_id));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_report_id);
       $query_update_A->execute();

           $full_base=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$monthly_report_id);
	           
	             drupal_goto($full_base);


           }

           else
           {


           
            $maxresult=db_query('select  max(monthly_form_id) maxsl from labour_factory_statcell_form_5');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
	     
		     $area=NULL;
		     $area_id=NULL;
		     $i=1;
           foreach( $zone as $a){
	       $query_zone=db_query('select  *  from fa_zone where  zone_id = :znid', array(':znid' => trim($a) ));

	        $result_zone=$query_zone->fetchAssoc();
		    
			
  
	          if($i > 1){
               $area.=","; 
               $area_id.=","; 
               }  
	           $area.=trim($result_zone['zone_name']);
	           $area_id.=trim($result_zone['zone_id']);
	           $i++;
	        
		  }
             //print_r($zone);

            // print $area;
	       //  exit;


                         $fieldsE = array('monthly_form_id' => $autoGENNO, 'inspector_id' =>$uid,'area' =>$area, 'report_from_date' => $from_date, 'report_to_date' => $to_date, 'report_year' => $from_brk[2], 'report_month' =>$from_brk[1],  'is_submitted' => 0 , 'status' => 'I' ,'last_updated' => date("Y-m-d"),  'is_processing' => 0 ,  'accept_by' => 0, 'accept_date' => NULL, 'e_note' => NULL,'processed_data' => NULL ,'create_by' => $uid,'create_date' => date("Y-m-d"),'area_id' => $area_id);
		  
		   
                     db_insert('labour_factory_statcell_form_5')->fields($fieldsE)->execute();	
	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$autoGENNO);
	           
	             drupal_goto($full_base);
	         }

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report-list';

             $message = 'MONTHLY REPORT NOT PROCEED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
	
}