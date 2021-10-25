
<?php

function monthly_report_list( $form, &$form_state   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	   $uid	=	$user->uid; 

	   //print "sssssssssssssss".$uid;

	   // $roleId=get_role_id($uid);
           
             //$role_name=get_role_name($roleId);

            // print $role_name;


     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');	
   
//$thisYear = date("Y")-1;
              $form['monthlyreportfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  Monthly Report   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
   $form['monthlyreportfield']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );

       
      /*  $form['month_option'] = array(
	     '#type' => 'value',
      
		  '#value' => array('1'=>t('January'),'2'=>t('February'),'3'=>t('March'),'4'=>t('April'),'5'=>t('May'),'6'=>t('June'),'7'=>t('July'),'8'=>t('August'),'9'=>t('September'),'10'=>t('October'),'11'=>t('November'),'12'=>t('December'))
		
         );
	
	
	
		$form['monthlyreportfield']['month'] = array(
		
        '#type' => 'select',
        '#title'=>'Month:',
		'#required' => TRUE,
        '#options' => $form['month_option']['#value'],
	    

		    '#prefix' => '<table  > <tr><td>', 
   
		    '#suffix'=>'</td>',

		    //'#attributes' => array('onchange' => 'annualReport(this.value);','class' => array('select-estab-shop')),
		
		
        
            );

		$form['year_option'] = array(
	     '#type' => 'value',
      
		  '#value' => array(date("Y")-1=>t(date("Y")-1), date("Y")=>t(date("Y")), date("Y")+1=>t(date("Y")+1), date("Y")+2=>t(date("Y")+2), date("Y")+3=>t(date("Y")+3))
		
         );

		$form['monthlyreportfield']['year'] = array(
		
        '#type' => 'select',
        '#title'=>'Year:',
		'#required' => TRUE,
        '#options' => $form['year_option']['#value'],
	  

		 '#prefix' => '<td>', 
   
		 '#suffix'=>'</td></tr>',

		    //'#attributes' => array('onchange' => 'annualReport(this.value);','class' => array('select-estab-shop')),
		
		
		
				
        
            ); */


            $form['monthlyreportfield']['from'] = array
              (
		      
		      
		    '#title' => t('From: '),
           

               '#type' => 'textfield',
                '#size' => 12,
                 '#attributes' => array('class' => array('datepicker_retify') ,  'autocomplete' => 'off'),
	       

		     
		     // '#attributes' => array('readonly' => 'readonly'),
	           '#required' => TRUE,
	           '#prefix' => '<tr><td colspan="2">', 
   
		    '#suffix'=>'</td></tr>',
	   
           ); 

           $form['monthlyreportfield']['to'] = array
              (
		  
		     
		    '#title' => t('To: '),
            

             '#type' => 'textfield',
                '#size' => 12,
                 '#attributes' => array('class' => array('datepicker_retify') , 'autocomplete' => 'off'),
	       
	  
	        '#required' => TRUE,
		  
		    '#prefix' => '<tr><td colspan="2">', 
   
		    '#suffix'=>'</td></tr>',
		        
	   
	   
           ); 

        $options_zone = array(0 => " Select  ") + anr_zone_option();
         
          $form['monthlyreportfield']['anr_zone'] = array (
                    '#type' => 'select',
                    '#title' => ('Zone'),
				    '#options' 		 => $options_zone,
			    	
		            '#required' => TRUE,
					 '#multiple'     =>  true,
					  '#attributes' => array('style' => array('height: 100px;')),
				
	             '#prefix' => '<tr><td colspan="2" >', 
   
		        '#suffix'=>'</td></tr>',
	                '#rows'        => 10,
               );
	   
	   
	   
	   
          	$form['monthlyreportfield']['submit_button']	= array(
																 
                                                               '#prefix' => '<tr><td colspan="2" style="text-align: center;">', 
   
		                                                          '#suffix'=>'</td></tr></table>',
																'#type'					=>'submit',
																'#value'				=>t(' Next ')
																);
		 
	
	  
		 
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
           if(trim($data->is_submitted) && trim($data->status)=='FD'){
		   
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

		}
		elseif(trim($data->is_submitted) && trim($data->status)=='FS'){
		   
		   $mr_status='Forward to Statistical Unit';
          
		    $kk=$base_root.$base_path.'admin/monthly-report-print/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}
		elseif(!trim($data->is_submitted)  && trim($data->status) =='I' )
		{
			$mr_status='Incomplete';
            $kk=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$data->monthly_form_id);
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


   // $month=trim($val['month']);
  //  $year=trim($val['year']);
	$uid=trim($val['uid']);
	//$from=$val['from']['year'].'-'.$val['from']['month'].'-'.$val['from']['day'];
	//$to=$val['to']['year'].'-'.$val['to']['month'].'-'.$val['to']['day'];
	
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
            $maxresult=db_query('select  max(monthly_form_id) maxsl from labour_factory_statcell_form_5');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
	     
		     $area=NULL;
		     $i=1;
           foreach( $zone as $a){
	       $query_zone=db_query('select  *  from fa_zone where  zone_id = :znid', array(':znid' => trim($a) ));

	        $result_zone=$query_zone->fetchAssoc();
		    
			
  
	          if($i > 1)
               $area.=","; 
	           $area.=trim($result_zone['zone_name']);
	           $i++;
	        
		  }
             //print_r($zone);

            // print $area;
	       //  exit;


                         $fieldsE = array('monthly_form_id' => $autoGENNO, 'inspector_id' =>$uid,'area' =>$area, 'report_from_date' => $from_date, 'report_to_date' => $to_date, 'report_year' => $from_brk[2], 'report_month' =>$from_brk[1],  'is_submitted' => 0 , 'status' => 'I' ,'last_updated' => date("Y-m-d"),  'is_processing' => 0 ,  'accept_by' => 0, 'accept_date' => NULL, 'e_note' => NULL,'processed_data' => NULL ,'create_by' => $uid,'create_date' => date("Y-m-d"));
		  
		   
                     db_insert('labour_factory_statcell_form_5')->fields($fieldsE)->execute();	
	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$autoGENNO);
	           
	             drupal_goto($full_base);

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