
<?php

function annual_report_list( $form, &$form_state   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	   $uid	=	$user->uid; 

	  // $uid	='23565';

	  // print "sssssssssss".$uid;


$form['#attached']['js'] = array(drupal_get_path('module', 'annual_report') . '/js/annualreport.js',);	
   
      $thisYear = date("Y")-1;
           $form['annulreportfield'] = array(
          '#title' => t('Annual Report : '.$thisYear.''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
   $form['annulreportfield']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );

        

        $form['report_for_option'] = array(
	     '#type' => 'value',
      
		   '#value' => array('CALENDAR'=>t('Calendar Year'),'FINANCIAL'=>t('Financial Year'))
		
         );
	
	
	
		$form['annulreportfield']['annual_report'] = array(
		
        '#type' => 'select',
        '#title'=>'Report For:',
		'#required' => TRUE,
        '#options' => $form['report_for_option']['#value'],
	      '#prefix' => '<div class="form-group row"><div class="col-sm-3">', 
   
		    '#suffix'=>'</div>',

		    '#attributes' => array('onchange' => 'annualReport(this.value);','class' => array('select-estab-shop')),
		
		
		
				
        
            );


            $form['annulreportfield']['from'] = array
              (
		       '#prefix' => '<div class="col-sm-3">', 
		       	'#title'=>'From:',
		       '#type' => 'textfield',
                '#size' => 12,

		        '#suffix'=>'</div>',
		        '#attributes' => array('readonly' => 'readonly'),
	           '#required' => TRUE,
	   
           ); 

           $form['annulreportfield']['to'] = array
              (
		       '#prefix' => ' <div class="col-sm-3">', 
		       '#type' => 'textfield',
                '#size' => 12,
              	'#title'=>'To:',
		        '#suffix'=>'</div>',
		        '#attributes' => array('readonly' => 'readonly'),
		         '#required' => TRUE,
	   
	   
           ); 

           $options_zone = array(0 => " Select  ") + anr_zone_option();
         
          $form['annulreportfield']['anr_zone'] = array (
                    '#type' => 'select',
                    '#title' => ('Zone'),
				    '#options' 		 => $options_zone,
			    	
		           // '#required' => TRUE,
					 '#multiple'     =>  true,
					  '#attributes' => array('style' => array('height: 100px;')),
				
	               '#prefix' 		 	=> '<div class="col-md-3"> ',
	               '#suffix' 		 	=> '</div>',
	                '#rows'        => 10,
               );
	   
	   
	   
	   
          	$form['annulreportfield']['submit_button']	= array(
																 
                                                               '#prefix' => '<div style="text-align:right;" class="col-sm-12" >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Next '),
																'#element_validate' => array('annual_report_validate'),
																);
		 
	
	  
		 
	 $rows = array();
    $header = array();

    	$header = array(
          array('data'=> 'SL.NO', 'class' => array('')),
		  array('data' => ' YEAR',   'class' => array('')),
		  array('data'=> 'From - To', 'class' => array('')),
          array('data' => 'Area', 'class' => array('')),
          array('data' => 'Status', 'class' => array('')),
          array('data' => 'Remarks', 'class' => array('')),
		  array('data' => 'EDIT/PRINT', 'class' => array('')),
		 
		 
		 
		 
	);	
	
	$query_oldinsid=db_query('select old_uid from tm_users where fa_uid = :fuid  ', array(':fuid' => trim($uid)));

    $result_oldinsId=$query_oldinsid->fetchAssoc();
    $old_uid = $result_oldinsId['old_uid']; 
    //print $uid.'=='.$old_uid;
    //if(!$old_uid) $old_uid='NULL';

	$sort = 'DESC';
	$order = 'annual_inspection_id';
	


	$annual_list_query = db_select('labour_factory_statcell_annual_report', 'p');
	$annual_list_query->fields('p',array('annual_inspection_id','inspector_id','report_from_date','report_to_date',
	'report_year','annual_form_type','status','submit_date','area','e_note','create_date','create_by','is_submitted','remarks','accept_by'));
	$annual_list_query->condition('p.inspector_id',trim($uid),'=');
	//$annual_list_query->orderBy($order, $sort);
	//$annual_list_query = $annual_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
	
	//$annual_list_query_2 = $annual_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
	//$annual_list_query->union($annual_list_query_2, 'UNION');
    if($old_uid){
	$annual_list_query_2 = db_select('labour_factory_statcell_annual_report', 't');
	
	$annual_list_query_2->innerjoin('tm_users', 'tu', '  tu.old_uid = t.inspector_id');
	
	$annual_list_query_2->fields('t',array('annual_inspection_id','inspector_id','report_from_date','report_to_date',
	'report_year','annual_form_type','status','submit_date','area','e_note','create_date','create_by','is_submitted','remarks','accept_by'));
	$annual_list_query_2->condition('t.inspector_id',trim($old_uid),'=');
	$annual_list_query_2->orderBy($order, $sort);

	$annual_list_query->union($annual_list_query_2, 'UNION');
    }
   

    //$annual_list_query = $annual_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
    
    //print $annual_list_query;


	
	$annual_list_query_result = $annual_list_query->execute();
	
	//print $ins_list_query;
	$i=0;
	foreach($annual_list_query_result as $data){
		$i++;
           $link_create_annual_report=NULL;
           $kk=NULL;
           $status_text=NULL;
           $name_deputy_director =NULL;

           if(trim($data->is_submitted)  && trim($data->status) =='FD' ){

           	$query_namedd=db_query('select fname from fa_employee_details where uid = :fuid  ', array(':fuid' => trim($data->accept_by)));

          $result_deputy_dir=$query_namedd->fetchAssoc();
          $name_deputy_director = $result_deputy_dir['fname'];
		   
            $status_text='Forward to Deputy Director ('. $name_deputy_director.')';

		    $kk=$base_root.$base_path.'admin/annual-report-print/'.encryption_decryption_fun('encrypt',$data->annual_inspection_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}
		elseif(trim($data->is_submitted)  && trim($data->status) =='BI' ){
		     $status_text='Back to inspector';

             $kk=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',encryption_decryption_fun('encrypt',$data->annual_inspection_id));
		     $link_create_annual_report=l(t('<font color="DarkGreen"><b>EDIT</b></font></br>'), $kk,array('html'=>TRUE)) ;

		}
		elseif(trim($data->is_submitted)  && trim($data->status) =='FS' ){
		     $status_text='Forward to Statistical Unit';

		    $kk=$base_root.$base_path.'admin/annual-report-print/'.encryption_decryption_fun('encrypt',$data->annual_inspection_id);
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>Print</b></font></br>'), $kk, array('attributes' => array('target'=>'_blank'), 'html'=>TRUE)) ;

		}
		elseif(!trim($data->is_submitted)  && trim($data->status) =='I' )
		{
            $status_text='Incomplete';

            $kk=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$data->annual_inspection_id);
		    $link_create_annual_report=l(t('<font color="DarkGreen"><b>EDIT</b></font></br>'), $kk,array('html'=>TRUE)) ;

		}
       $anyear=NULL;
       if(trim($data->annual_form_type)=='CALENDAR')
		 $anyear=$data->report_year;
       elseif(trim($data->annual_form_type)=='FINANCIAL')
		 $anyear=$data->report_year.'-'.($data->report_year + 1);

	$rows[] = array(
      				
					$i,
					
					//$data->annual_form_type.'&nbsp; YEAR',
					$anyear,
					
					date('d/m/Y', strtotime($data->report_from_date)).'-'.date('d/m/Y', strtotime($data->report_to_date)),
					
					$data->area,
					$status_text,
					$data->remarks,
					$link_create_annual_report,
					
					
					
				);


}
				$variables = array(
	  			  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard table-bordered sticky-enabled')),
	  			'header' 			=> $header,
	  			'rows'				=> $rows,
		);
		$output = theme('table', $variables).theme("pager");
	     $form['inspectionlistfields']['addshowprin'] = array(
					'#markup'=>$output,
					);
	
		

	   
	
	   
       return $form; 
  }
  function annual_report_validate($element,&$form_state)
  {
  
    $val=$form_state['values'];
    $uid=trim($val['uid']);
    $from=trim($val['from']);
    $to=trim($val['to']);

    //print $uid.'='.$from.'='.$to;
    //exit;
   
     $ann_report=db_query('select  * from labour_factory_statcell_annual_report where  inspector_id=:filenumber and report_from_date=:fdt and report_to_date=:tdt', array(':filenumber' => $uid , ':fdt' => $from , ':tdt' => $to) );
		
	      if($ann_report->rowCount() > 0) 
          { 
	  
	 
	  form_error($element, t(' Annual report already exist  . '));
	 
		 
	   
          
		 }
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

function annual_report_list_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);
//exit;


    $annual_report=trim($val['annual_report']);
	$uid=trim($val['uid']);
	$from=trim($val['from']);
	$to=trim($val['to']);
	$thisYear = date("Y")-1;

	

	$zone = array_filter($form_state['values']['anr_zone']);
	//print print_r($zone);
	//exit;

 $txn = db_transaction();
	  try {
            $maxresult=db_query('select  max(annual_inspection_id) maxsl from labour_factory_statcell_annual_report');	
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
               $area.=","   ; 
	           $area.=trim($result_zone['zone_name']);
	           $i++;
	        
		  }
             //print_r($zone);

            // print $area;
	       //  exit;


                         $fieldsE = array('annual_inspection_id' => $autoGENNO, 'inspector_id' =>$uid,'area' =>$area, 'report_from_date' => $from, 'report_to_date' => $to, 'report_year' => $thisYear, 'annual_form_type' => $annual_report, 'status' => 'I', 'remarks' => NULL
                         , 'status_code' => NULL, 'last_updated' => date("Y-m-d"), 'is_submitted' => 0,  'is_processing' => 0 , 'is_accepted' => 0, 'accept_by' => 0, 'accept_date' => NULL, 'e_note' => NULL,'processed_data' => NULL ,'is_disabled' => 0,'create_by' => $uid,'create_date' => date("Y-m-d") );
		  
		   
             db_insert('labour_factory_statcell_annual_report')->fields($fieldsE)->execute();	
	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$autoGENNO);
	           
	             drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'factory/annual-report-list';

             $message = 'ANNUAL REPORT NOT PROCEED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
	
}





function annual_report_step1( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	 $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	 
	 //print $id;
	   $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
    $result_mrist=$mr_istquery_result->fetchAssoc();
    $area=$result_mrist['area'];
     $inspector_id=trim($result_mrist['inspector_id']);
     $inspector_name=get_name($inspector_id);
     $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
     $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));

	 $form['step1field'] = array(
          '#title' => t(' Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		$form['step1field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

	    $g_nouv_regfac_2m_i=NULL;


		$g_nouv_regfac_2m_ii=NULL;

		$g_nouv_regfac_85=NULL;
		//print $g_nouv_regfac_2m_ii. '/'.$g_nouv_regfac_85;
		$g_nouv_unregfac_2m_i=NULL;
		$g_nouv_unregfac_2m_ii=NULL;
		$g_nouv_unregfac_85=NULL;
		$g_nouv_non_amendable=NULL;
		$g_nouv_total=NULL;

		$g_novp_regfac_2m_i=NULL;
		$g_novp_regfac_2m_ii=NULL;
		$g_novp_regfac_85=NULL;
		$g_novp_unregfac_2m_i=NULL;
		$g_novp_unregfac_2m_ii=NULL;
		$g_novp_unregfac_85=NULL;
		$g_novp_non_amendable=NULL;
		$g_novp_total=NULL;





		$h_nouv_regfac_2m_i=NULL;
		$h_nouv_regfac_2m_ii=NULL;
		$h_nouv_regfac_85=NULL;
		$h_nouv_unregfac_2m_i=NULL;
		$h_nouv_unregfac_2m_ii=NULL;
		$h_nouv_unregfac_85=NULL;
		$h_nouv_non_amendable=NULL;
		$h_nouv_total=NULL;


		$h_novp_regfac_2m_i=NULL;
		$h_novp_regfac_2m_ii=NULL;
		$h_novp_regfac_85=NULL;
		$h_novp_unregfac_2m_i=NULL;
		$h_novp_unregfac_2m_ii=NULL;
		$h_novp_unregfac_85=NULL;
		$h_novp_non_amendable=NULL;
		$h_novp_total=NULL;


		$mah_nouv_regfac_2m_i=NULL;
		$mah_nouv_regfac_2m_ii=NULL;
		$mah_nouv_regfac_85=NULL;
		$mah_nouv_unregfac_2m_i=NULL;
		$mah_nouv_unregfac_2m_ii=NULL;
		$mah_nouv_unregfac_85=NULL;
		$mah_nouv_non_amendable=NULL;
		$mah_nouv_total=NULL;






		$mah_novp_regfac_2m_i=NULL;
		$mah_novp_regfac_2m_ii=NULL;
		$mah_novp_regfac_85=NULL;
		$mah_novp_unregfac_2m_i=NULL;
		$mah_novp_unregfac_2m_ii=NULL;
		$mah_novp_unregfac_85=NULL;
		$mah_novp_non_amendable=NULL;
		$mah_novp_total=NULL;





		
      
		$visit_msihcr=NULL;;
		$visit_pwa=NULL;;
		$visit_mba=NULL;;
		$visit_car=NULL;;
		$visit_clpra=NULL;;
		$visit_rest_interval=NULL;;
		$visit_bef_after_legal_hours=NULL;;
		$visit_sunday_holiday=NULL;;
		$visit_approval_of_plan=NULL;;
		$visit_renew_licence=NULL;;


		$visit_collection_statistics=NULL;;
		$visit_enq_complaints=NULL;;
		$visit_court_prosecution=NULL;;
		$visit_to_closed_factory=NULL;;
		$visit_others=NULL;;
		$visit_total=NULL;;											
		
        if(trim($filenumber)){
	
	      $step1_select_query = db_select('labour_factory_statcell_annual_report_t1_a_b', 'a');
       
        $step1_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step1_select_query->fields('a',array('g_nouv_regfac_2m_i','g_nouv_regfac_2m_ii','g_nouv_regfac_85','g_nouv_unregfac_2m_i','g_nouv_unregfac_2m_ii','g_nouv_unregfac_85','g_nouv_non_amendable','g_nouv_total', 'g_novp_regfac_2m_i','g_novp_regfac_2m_ii','g_novp_regfac_85','g_novp_unregfac_2m_i','g_novp_unregfac_2m_ii','g_novp_unregfac_85','g_novp_non_amendable','g_novp_total','h_nouv_regfac_2m_i','h_nouv_regfac_2m_ii','h_nouv_regfac_85','h_nouv_unregfac_2m_i','h_nouv_unregfac_2m_ii','h_nouv_unregfac_85','h_nouv_non_amendable','h_nouv_total',
        'h_novp_regfac_2m_i','h_novp_regfac_2m_ii','h_novp_regfac_85','h_novp_unregfac_2m_i','h_novp_unregfac_2m_ii','h_novp_unregfac_85','h_novp_non_amendable','h_novp_total',
        'mah_nouv_regfac_2m_i','mah_nouv_regfac_2m_ii','mah_nouv_regfac_85','mah_nouv_unregfac_2m_i','mah_nouv_unregfac_2m_ii','mah_nouv_unregfac_85','mah_nouv_non_amendable','mah_nouv_total','mah_novp_regfac_2m_i','mah_novp_regfac_2m_ii','mah_novp_regfac_85','mah_novp_unregfac_2m_i','mah_novp_unregfac_2m_ii','mah_novp_unregfac_85','mah_novp_non_amendable','mah_novp_total'));
        $step1_select_query_result = $step1_select_query->execute(); 
		
		$result_step1_A=$step1_select_query_result->fetchAssoc();
		$g_nouv_regfac_2m_i=$result_step1_A['g_nouv_regfac_2m_i'];


		$g_nouv_regfac_2m_ii=$result_step1_A['g_nouv_regfac_2m_ii'];

		$g_nouv_regfac_85=$result_step1_A['g_nouv_regfac_85'];
		//print $g_nouv_regfac_2m_ii. '/'.$g_nouv_regfac_85;
		$g_nouv_unregfac_2m_i=$result_step1_A['g_nouv_unregfac_2m_i'];
		$g_nouv_unregfac_2m_ii=$result_step1_A['g_nouv_unregfac_2m_ii'];
		$g_nouv_unregfac_85=$result_step1_A['g_nouv_unregfac_85'];
		$g_nouv_non_amendable=$result_step1_A['g_nouv_non_amendable'];
		$g_nouv_total=$result_step1_A['g_nouv_total'];

		$g_novp_regfac_2m_i=$result_step1_A['g_novp_regfac_2m_i'];
		$g_novp_regfac_2m_ii=$result_step1_A['g_novp_regfac_2m_ii'];
		$g_novp_regfac_85=$result_step1_A['g_novp_regfac_85'];
		$g_novp_unregfac_2m_i=$result_step1_A['g_novp_unregfac_2m_i'];
		$g_novp_unregfac_2m_ii=$result_step1_A['g_novp_unregfac_2m_ii'];
		$g_novp_unregfac_85=$result_step1_A['g_novp_unregfac_85'];
		$g_novp_non_amendable=$result_step1_A['g_novp_non_amendable'];
		$g_novp_total=$result_step1_A['g_novp_total'];





		$h_nouv_regfac_2m_i=$result_step1_A['h_nouv_regfac_2m_i'];
		$h_nouv_regfac_2m_ii=$result_step1_A['h_nouv_regfac_2m_ii'];
		$h_nouv_regfac_85=$result_step1_A['h_nouv_regfac_85'];
		$h_nouv_unregfac_2m_i=$result_step1_A['h_nouv_unregfac_2m_i'];
		$h_nouv_unregfac_2m_ii=$result_step1_A['h_nouv_unregfac_2m_ii'];
		$h_nouv_unregfac_85=$result_step1_A['h_nouv_unregfac_85'];
		$h_nouv_non_amendable=$result_step1_A['h_nouv_non_amendable'];
		$h_nouv_total=$result_step1_A['h_nouv_total'];


		$h_novp_regfac_2m_i=$result_step1_A['h_novp_regfac_2m_i'];
		$h_novp_regfac_2m_ii=$result_step1_A['h_novp_regfac_2m_ii'];
		$h_novp_regfac_85=$result_step1_A['h_novp_regfac_85'];
		$h_novp_unregfac_2m_i=$result_step1_A['h_novp_unregfac_2m_i'];
		$h_novp_unregfac_2m_ii=$result_step1_A['h_novp_unregfac_2m_ii'];
		$h_novp_unregfac_85=$result_step1_A['h_novp_unregfac_85'];
		$h_novp_non_amendable=$result_step1_A['h_novp_non_amendable'];
		$h_novp_total=$result_step1_A['h_novp_total'];


		$mah_nouv_regfac_2m_i=$result_step1_A['mah_nouv_regfac_2m_i'];
		$mah_nouv_regfac_2m_ii=$result_step1_A['mah_nouv_regfac_2m_ii'];
		$mah_nouv_regfac_85=$result_step1_A['mah_nouv_regfac_85'];
		$mah_nouv_unregfac_2m_i=$result_step1_A['mah_nouv_unregfac_2m_i'];
		$mah_nouv_unregfac_2m_ii=$result_step1_A['mah_nouv_unregfac_2m_ii'];
		$mah_nouv_unregfac_85=$result_step1_A['mah_nouv_unregfac_85'];
		$mah_nouv_non_amendable=$result_step1_A['mah_nouv_non_amendable'];
		$mah_nouv_total=$result_step1_A['mah_nouv_total'];






		$mah_novp_regfac_2m_i=$result_step1_A['mah_novp_regfac_2m_i'];
		$mah_novp_regfac_2m_ii=$result_step1_A['mah_novp_regfac_2m_ii'];
		$mah_novp_regfac_85=$result_step1_A['mah_novp_regfac_85'];
		$mah_novp_unregfac_2m_i=$result_step1_A['mah_novp_unregfac_2m_i'];
		$mah_novp_unregfac_2m_ii=$result_step1_A['mah_novp_unregfac_2m_ii'];
		$mah_novp_unregfac_85=$result_step1_A['mah_novp_unregfac_85'];
		$mah_novp_non_amendable=$result_step1_A['mah_novp_non_amendable'];
		$mah_novp_total=$result_step1_A['mah_novp_total'];





		
        $step1_select_B_query = db_select('labour_factory_statcell_annual_report_t1_d', 'b');
       
        $step1_select_B_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
        $step1_select_B_query->fields('b',array('visit_msihcr','visit_pwa','visit_mba','visit_car','visit_clpra','visit_rest_interval','visit_bef_after_legal_hours','visit_sunday_holiday', 'visit_approval_of_plan','visit_renew_licence','visit_collection_statistics','visit_enq_complaints','visit_court_prosecution','visit_to_closed_factory','visit_others','visit_total'));
        $step1_select_B_query_result = $step1_select_B_query->execute(); 
		
		$result_step1_B=$step1_select_B_query_result->fetchAssoc();
		$visit_msihcr=$result_step1_B['visit_msihcr'];
		$visit_pwa=$result_step1_B['visit_pwa'];
		$visit_mba=$result_step1_B['visit_mba'];
		$visit_car=$result_step1_B['visit_car'];
		$visit_clpra=$result_step1_B['visit_clpra'];
		$visit_rest_interval=$result_step1_B['visit_rest_interval'];
		$visit_bef_after_legal_hours=$result_step1_B['visit_bef_after_legal_hours'];
		$visit_sunday_holiday=$result_step1_B['visit_sunday_holiday'];
		$visit_approval_of_plan=$result_step1_B['visit_approval_of_plan'];
		$visit_renew_licence=$result_step1_B['visit_renew_licence'];


		$visit_collection_statistics=$result_step1_B['visit_collection_statistics'];
		$visit_enq_complaints=$result_step1_B['visit_enq_complaints'];
		$visit_court_prosecution=$result_step1_B['visit_court_prosecution'];
		$visit_to_closed_factory=$result_step1_B['visit_to_closed_factory'];
		$visit_others=$result_step1_B['visit_others'];
		$visit_total=$result_step1_B['visit_total'];

		
		 }
	 
	
	      
	
	
	 $form['#attached']['js'] = array(drupal_get_path('module', 'annual_report') . '/js/annualreport.js',);	
		
	 $form['step1Bfield'] = array(
          '#title' => t('<font color="DarkGreen"><b> Inspection (A)   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     $form['step1field']['one'] = array
              (
		       '#prefix' => '<table class="table"><tr><td rowspan="4" >', 
		       '#markup'=>'<b> Group  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	


            $form['step1field']['two'] = array
              (
		       '#prefix' => '<td colspan="8" style="text-align:center;">', 
		       '#markup'=>'<b> No. of units visited  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	


             $form['step1field']['three'] = array
              (
		       '#prefix' => '<tr><td colspan="3" >', 
		       '#markup'=>'<b> Registered factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['four'] = array
              (
		       '#prefix' => '<td colspan="3" >', 
		       '#markup'=>'<b> Unregistered amenable factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['five'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Not amenable factories  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['six'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['2mone'] = array
              (
		       '#prefix' => '<tr><td colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b>2(m)  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
            	

            $form['step1field']['85one'] = array
              (
		       '#prefix' => '<td rowspan="2"  >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['2mtwo'] = array
              (
		       '#prefix' => '<td  colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b> 2(m) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1field']['85two'] = array
              (
		       '#prefix' => '<td rowspan="2" >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['romani'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1field']['romanii'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['romaniii'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
           $form['step1field']['romaniv'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii)</b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['Gf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>G </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1field']['Gfone'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
		       '#size' => 2,
		       '#default_value' =>$g_nouv_regfac_2m_i ,

		       '#suffix'=>'</td>',
		       '#attributes' => array("onkeyup" => "addIA('G');"),
	   
	   
           );

                $form['step1field']['Gftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',

		        '#default_value' =>$g_nouv_regfac_2m_ii ,  
		        '#attributes' => array('onkeyup' => "addIA('G');"), 
	   
	   
           );
               $form['step1field']['Gfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		        '#default_value' =>$g_nouv_regfac_85   ,
		         '#attributes' => array('onkeyup' => "addIA('G');"),    
	   
	   
           );

              $form['step1field']['Gffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',

	           '#default_value' =>$g_nouv_unregfac_2m_i  ,
	            '#attributes' => array('onkeyup' => "addIA('G');"),   
	   
           );
			 $form['step1field']['Gffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	      '#default_value' =>$g_nouv_unregfac_2m_ii ,
	       '#attributes' => array('onkeyup' => "addIA('G');"),   
	   
           );	

           $form['step1field']['Gfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	     '#default_value' =>$g_nouv_unregfac_85  ,
	      '#attributes' => array('onkeyup' => "addIA('G');"),   
           );	

           $form['step1field']['Gfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		     '#default_value' =>$g_nouv_non_amendable   ,
		      '#attributes' => array('onkeyup' => "addIA('G');"),       
	   
	   
           );	
		   //print "aaaaaaaaaaaa".$g_nouv_total;
            $form['step1field']['Gfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	      '#default_value' =>$g_nouv_total      ,
	       //'#attributes' => array('onkeyup' => "addIA('G');"),    
	   
           );	

            $form['step1field']['Hf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>H </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1field']['Hfone'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		       '#suffix'=>'</td>',
		        '#default_value' =>$h_nouv_regfac_2m_i  ,
		          '#attributes' => array('onkeyup' => "addIA('H');"),
	   
	   
           );

                $form['step1field']['Hftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_regfac_2m_ii ,
		         '#attributes' => array('onkeyup' => "addIA('H');"),
	   
           );
               $form['step1field']['Hfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	             '#default_value' =>$h_nouv_regfac_85  ,
		          '#attributes' => array('onkeyup' => "addIA('H');"),
	   
           );

              $form['step1field']['Hffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_unregfac_2m_i ,
		        '#attributes' => array('onkeyup' => "addIA('H');"), 
	   
           );
			 $form['step1field']['Hffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	        '#default_value' =>$h_nouv_unregfac_2m_ii  ,
		        '#attributes' => array('onkeyup' => "addIA('H');"),
	   
           );	

           $form['step1field']['Hfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_unregfac_85,
		        '#attributes' => array('onkeyup' => "addIA('H');"), 
	   
           );	

           $form['step1field']['Hfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	           '#default_value' =>$h_nouv_non_amendable ,
	            '#attributes' => array('onkeyup' => "addIA('H');"), 
           );	
            $form['step1field']['Hfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	          '#default_value' =>$h_nouv_total
	   
           );	

            $form['step1field']['MAHf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>MAH </b>',

		          '#suffix'=>'</td>',
	           
	   
           );	

               $form['step1field']['MAHfone'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',

		         '#default_value' =>$mah_nouv_regfac_2m_i  ,
	            '#attributes' => array('onkeyup' => "addIA('M');"),  
	   
	   
           );

                $form['step1field']['MAHftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$mah_nouv_regfac_2m_ii  ,
	     '#attributes' => array('onkeyup' => "addIA('M');"),     
	   
           );
               $form['step1field']['MAHfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	        '#default_value' =>$mah_nouv_regfac_85 ,
	          '#attributes' => array('onkeyup' => "addIA('M');"),    
	   
           );

              $form['step1field']['MAHffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	         '#default_value' =>$mah_nouv_unregfac_2m_i   ,
	           '#attributes' => array('onkeyup' => "addIA('M');"),      
	   
           );
			 $form['step1field']['MAHffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   '#default_value' =>$mah_nouv_unregfac_2m_ii    ,
	     '#attributes' => array('onkeyup' => "addIA('M');"),    
	   
           );	

           $form['step1field']['MAHfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',

	    '#default_value' =>$mah_nouv_unregfac_85   ,
	      '#attributes' => array('onkeyup' => "addIA('M');"),     
	   
           );	

           $form['step1field']['MAHfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		       '#default_value' =>$mah_nouv_non_amendable  ,
		         '#attributes' => array('onkeyup' => "addIA('M');"),       
	   
	   
           );	
            $form['step1field']['MAHfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
                '#default_value' =>$mah_nouv_total  ,    
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );	


   // Part B 


   $form['step1Bfield'] = array(
          '#title' => t('<font color="DarkGreen"><b> Inspection (B)   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		

														
		
       
	
	  
		 
	 
	
	      
	
	
	
		
	

		
     $form['step1Bfield']['oneB'] = array
              (
		       '#prefix' => '<table class="table"><tr><td rowspan="4" >', 
		       '#markup'=>'<b> Group  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	


            $form['step1Bfield']['twoB'] = array
              (
		       '#prefix' => '<td colspan="8" style="text-align:center;">', 
		       '#markup'=>'<b> No. of visits paid to </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	


             $form['step1Bfield']['threeB'] = array
              (
		       '#prefix' => '<tr><td colspan="3" >', 
		       '#markup'=>'<b> Registered factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['fourB'] = array
              (
		       '#prefix' => '<td colspan="3" >', 
		       '#markup'=>'<b> Unregistered amenable factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['fiveB'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Not amenable factories  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['sixB'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['2moneB'] = array
              (
		       '#prefix' => '<tr><td colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b>2(m)  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
            	

            $form['step1Bfield']['85oneB'] = array
              (
		       '#prefix' => '<td rowspan="2"  >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['2mtwoB'] = array
              (
		       '#prefix' => '<td  colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b> 2(m) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1Bfield']['85twoB'] = array
              (
		       '#prefix' => '<td rowspan="2" >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['romaniB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1Bfield']['romaniiB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['romaniiiB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
           $form['step1Bfield']['romanivB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii)</b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['GfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>G </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['GfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		      '#suffix'=>'</td>',
		      '#default_value' =>$g_novp_regfac_2m_i  ,
		       '#attributes' => array('onkeyup' => "addIB('G');"),
	   
	   
           );

                $form['step1Bfield']['GftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$g_novp_regfac_2m_ii  ,
	             '#attributes' => array('onkeyup' => "addIB('G');"),
	   
           );
               $form['step1Bfield']['GfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
		          '#default_value' =>$g_novp_regfac_85  ,
		       '#attributes' => array('onkeyup' => "addIB('G');"),
	   
	   
           );

              $form['step1Bfield']['GffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	           '#default_value' =>$g_novp_unregfac_2m_i  ,
	              '#attributes' => array('onkeyup' => "addIB('G');"),
	   
           );
			 $form['step1Bfield']['GffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	            '#default_value' =>$g_novp_unregfac_2m_ii  ,
	           '#attributes' => array('onkeyup' => "addIB('G');"),
	   
           );	

           $form['step1Bfield']['GfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	           '#default_value' =>$g_novp_unregfac_85  ,
	              '#attributes' => array('onkeyup' => "addIB('G');"),
	   
           );	

           $form['step1Bfield']['GfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	           '#default_value' =>$g_novp_non_amendable  ,
	            '#attributes' => array('onkeyup' => "addIB('G');"),  
	   
           );	
            $form['step1Bfield']['GfeightddB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',

		       '#default_value' =>$g_novp_total  ,    
	   
	   
           );	

            $form['step1Bfield']['HfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>H </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['HfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	          '#default_value' =>$h_novp_regfac_2m_i  , 
	           '#attributes' => array('onkeyup' => "addIB('H');"),     
	   
           );

                $form['step1Bfield']['HftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$h_novp_regfac_2m_ii  ,
	     '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );
               $form['step1Bfield']['HfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$h_novp_regfac_85  ,
	           '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );

              $form['step1Bfield']['HffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	    '#default_value' =>$h_novp_unregfac_2m_i  ,
	     '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );
			 $form['step1Bfield']['HffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	      '#default_value' =>$h_novp_unregfac_2m_ii  ,
	      '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );	

           $form['step1Bfield']['HfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	       '#default_value' =>$h_novp_unregfac_85  ,
	       '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );	

           $form['step1Bfield']['HfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
               '#size' => 2,
		       '#suffix'=>'</td>',
	     '#default_value' =>$h_novp_non_amendable  ,
	     '#attributes' => array('onkeyup' => "addIB('H');"),  
	   
           );	
            $form['step1Bfield']['HfeightB'] = array
              (
		      '#prefix' => '<td >', 
		      '#type' => 'textfield',
              '#size' => 2,
		      '#suffix'=>'</td></tr>',
	          '#default_value' =>$h_novp_total  ,
	   
           );	

            $form['step1Bfield']['MAHfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>MAH </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['MAHfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	         '#default_value' =>$mah_novp_regfac_2m_i  ,
	           '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );

                $form['step1Bfield']['MAHftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	      '#default_value' =>$mah_novp_regfac_2m_ii  ,
	        '#attributes' => array('onkeyup' => "addIB('M');"),  
           );
               $form['step1Bfield']['MAHfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$mah_novp_regfac_85  ,
	      '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );

              $form['step1Bfield']['MAHffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   '#default_value' =>$mah_novp_unregfac_2m_i  ,
	     '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );
			 $form['step1Bfield']['MAHffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$mah_novp_unregfac_2m_ii  ,
	      '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );	

           $form['step1Bfield']['MAHfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$mah_novp_unregfac_85  ,
	      '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );	

           $form['step1Bfield']['MAHfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   '#default_value' =>$mah_novp_non_amendable  ,
	     '#attributes' => array('onkeyup' => "addIB('M');"),  
	   
           );	
            $form['step1Bfield']['MAHfeightB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
               '#size' => 2,
               '#default_value' =>$mah_novp_total  ,
	   
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );           




     // Part 3

              $form['step1Cfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  C.Frequency of Visit.  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
$form['step1Cfield']['col1'] = array
              (
		       '#prefix' => '<table class="table"><tr><td rowspan="2" >', 
		       '#markup'=>'<b> Frequency  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Cfield']['col2'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> Factories other than defence installations  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


               $form['step1Cfield']['col3'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> Defence Installation  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Cfield']['col4'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b>TOTAL  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );

               $form['step1Cfield']['col5'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#markup'=>'<b>Regd.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Cfield']['col6'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Un-registered (Amenable & Non-Amenable).  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Cfield']['col7'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Regd..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                  $form['step1Cfield']['col8'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>	Un-registered (Amenable & Non-Amenable)..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step1Cfield']['col9'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Regd..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Cfield']['col10'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>	Un-registered (Amenable & Non-Amenable)..  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );
        

        $form['frquency_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array('0'=>t('select  '),'1'=>t('1'),'2'=>t('2'),'3'=>t('3'), '4'=>t('4') , '5'=>t('5') , '6'=>t('6') ,'7'=>t('More than six times'))
		
         );
	
	
	
		$form['step1Cfield']['frquency'] = array(
		
        '#type' => 'select',
       // '#title'=>'Country',
		//'#required' => TRUE,
        '#options' => $form['frquency_option']['#value'],
	      '#prefix' => ' <tr> <td  >', 
   
		    '#suffix'=>'</td>',
		
		
		
				
        
            );

              $form['step1Cfield']['col2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#attributes' => array('onkeyup' => "frequenC('R');"),  
	   
	   
           ); 

               $form['step1Cfield']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		       '#attributes' => array('onkeyup' => "frequenC('U');"),  
	   
	   
           ); 


               $form['step1Cfield']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#attributes' => array('onkeyup' => "frequenC('R');"),  
	   
	   
           ); 



                $form['step1Cfield']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#attributes' => array('onkeyup' => "frequenC('U');"),  
	   
	   
           ); 



                $form['step1Cfield']['col6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

                $form['step1Cfield']['col7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


														
		
       $form['step1Cfield']['submit'] = array (
                          
		'#type' => 'button',
		'#event' => 'click',
		'#prefix' => '<tr><td colspan="8" style="text-align:center;">',  
         '#suffix' => '</td></tr></table>',
		   '#attributes' => array('class' => array('estab-btn-pad')),
        //'#disabled' => TRUE, 
        '#default_value' => 'ADD  ',
        '#ajax' => array(
        'callback' => 'add_ar_frq',
        'wrapper' => 'pr_person_add',
        'method' => 'html',
        'effect' => 'fade'
    )
        );
	
	  
		$output1='';
     if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t1_c where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
      $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL. NO</th>
      
       <th > Frequency</th>
	    <th >Regd</th>
       
		 <th >Un-registered</th>

		 <th >Regd</th>
       
		 <th >Un-registered</th>
		  <th >Regd</th>
       
		 <th >Un-registered</th>
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $frequency=$squan->frequency;
			  $not_defence_reg=$squan->not_defence_reg;
			  $not_defence_unreg=$squan->not_defence_unreg;
              $defence_reg=$squan->defence_reg;

              $defence_unreg=$squan->defence_unreg;

              $total_reg=$squan->total_reg;
              $total_unreg=$squan->total_unreg;
              
             
              	 if($frequency=='7')
              	$frequency='More than six times';
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-taba-partc-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t($img),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output1 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$frequency."</td>";
			    $output1.= "<td>".$not_defence_reg."</td>";
                $output1.= "<td>".$not_defence_unreg."</td>";
                $output1.= "<td>".$defence_reg."</td>";
                $output1.= "<td>".$defence_unreg."</td>";
                $output1.= "<td>".$total_reg."</td>";
                $output1.= "<td>".$total_unreg."</td>";
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table>"; 
			  
			

	
	   }
	}
	
	 $form['step1Cfield']['prpersonlist'] = array(
	 	'#prefix' => '<div align="left" id="pr_person_add">'.$output1,
		'#suffix' => '</div>',
       
	);

   


	 
	
	      
	
	
	// Part 4
		
	      $form['step1Dfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  D.No. of Visits paid.  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step1Dfield']['colD1'] = array
              (
		       '#prefix' => '<table class="table"><tr><td colspan="5" >', 
		       '#markup'=>'<b> Exclusive Under  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step1Dfield']['colD2'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> During Rest Interval  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Dfield']['colD3'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> Before or after legal hours  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Dfield']['colD4'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> On Sundays/Holidays </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step1Dfield']['colD5'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> For approval of plans </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step1Dfield']['colD6'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> For Renewal of licence </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step1Dfield']['colD7'] = array
              (
		       '#prefix' => ' <tr> <td  >', 
		        '#markup'=>'<b> MSIHCR </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step1Dfield']['colD8'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> P.W.A </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 
              $form['step1Dfield']['colD9'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> M.B.A </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step1Dfield']['colD10'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> C.A.R. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step1Dfield']['colD11'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> C.I.(P&R)A </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

           



               $form['step1Dfield']['misval'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	            '#default_value' =>$visit_msihcr  ,
	             '#attributes' => array('onkeyup' => "addVP();"),   
	   
           ); 

      $form['step1Dfield']['pwdval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	         '#default_value' =>$visit_pwa  ,
	          '#attributes' => array('onkeyup' => "addVP();"),   
           ); 


              $form['step1Dfield']['mbaval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	            '#default_value' =>$visit_mba ,
	             '#attributes' => array('onkeyup' => "addVP();"),    
	   
           );

              $form['step1Dfield']['carval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$visit_car  ,
		         '#attributes' => array('onkeyup' => "addVP();"),   
	   
	   
           );

               $form['step1Dfield']['cival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$visit_clpra   ,
		         '#attributes' => array('onkeyup' => "addVP();"),  
	   
	   
           );

                $form['step1Dfield']['drival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	            '#default_value' =>$visit_rest_interval   ,
	             '#attributes' => array('onkeyup' => "addVP();"),  
	   
	   
           );

                $form['step1Dfield']['balhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$visit_bef_after_legal_hours ,
		          '#attributes' => array('onkeyup' => "addVP();"),    
	   
	   
           );

               $form['step1Dfield']['oshhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$visit_sunday_holiday  ,
		           '#attributes' => array('onkeyup' => "addVP();"),   
	   
	   
           );
              $form['step1Dfield']['faopval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$visit_approval_of_plan ,
		       '#attributes' => array('onkeyup' => "addVP();"),         
	   
	   
           );

              $form['step1Dfield']['frolval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	           '#default_value' =>$visit_renew_licence  ,

	            '#attributes' => array('onkeyup' => "addVP();"),   
	   
           );

              $form['step1Dfield']['colD12'] = array
              (
		       '#prefix' => '<tr><td colspan="2">', 
		       '#markup'=>'<b> For collections of statistics </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD13'] = array
              (
		       '#prefix' => '<td colspan="2">', 
		       '#markup'=>'<b> For enquiry into complaints </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
              $form['step1Dfield']['colD14'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> To court for prosecution cases </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD15'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> To closed factories </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['colD16'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Others </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Dfield']['colD17'] = array
              (
		       '#prefix' => '<td  >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );
 $form['step1Dfield']['colD12val'] = array
              (
		       '#prefix' => '<tr> <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
		          '#default_value' =>$visit_collection_statistics ,  
	             '#maxlength' => 10,
	              '#attributes' => array('onkeyup' => "addVP();"),  
	   
           );


 $form['step1Dfield']['colD13val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
		        
		      '#default_value' =>$visit_enq_complaints  , 
	             '#maxlength' => 10,
	              '#attributes' => array('onkeyup' => "addVP();"),  
	   
           );

              $form['step1Dfield']['colD14val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	            '#default_value' =>$visit_court_prosecution ,  
	             '#maxlength' => 10,
	              '#attributes' => array('onkeyup' => "addVP();"),  
           );
              

              $form['step1Dfield']['colD15val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	        '#default_value' =>$visit_to_closed_factory   ,
	           '#maxlength' => 10,
	            '#attributes' => array('onkeyup' => "addVP();"),  
	   
           );

              $form['step1Dfield']['colD16val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
		           '#default_value' =>$visit_others   ,
		              '#maxlength' => 10,
	            '#attributes' => array('onkeyup' => "addVP();"),  
	   
           );

         $form['step1Dfield']['colD17val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td></tr> </table>',
	   
	          '#default_value' =>$visit_total ,
	             '#maxlength' => 10, 
	              //'#attributes' => array('onkeyup' => "addVP();"),   
           );


			$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }
  




      function add_ar_frq($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];

           //return trim($val['inspectionid']);
          // exit;
    
 
      $inspectionid=trim($val['inspectionid']);
      $frquency=trim($val['frquency']); if(!$frquency) $frquency= NULL;  
      $col2val=trim($val['col2val']);   if(!$col2val)   $col2val= NULL;  
      $col3val=trim($val['col3val']);   if(!$col3val)   $col3val= NULL;  
      $col4val=trim($val['col4val']);   if(!$col4val)   $col4val= NULL;  
      $col5val=trim($val['col5val']);   if(!$col5val)   $col5val= NULL;  
      $col6val=trim($val['col6val']);   if(!$col6val)   $col6val= NULL;  
      $col7val=trim($val['col7val']);   if(!$col7val)   $col7val= NULL;  

     if(!$frquency){
		   drupal_get_messages(error);
	       return "<font color='#FF3333'><b> please select frquency  <b>    </font>";
		   exit;
	   }


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t1_c ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'frequency' =>$frquency ,'not_defence_reg' =>$col2val,'not_defence_unreg' =>$col3val, 'defence_reg' => $col4val, 'defence_unreg' => $col5val, 'total_reg' => $col6val, 'total_unreg' => $col7val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t1_c')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t1_c where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
      
      $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Frequency</th>
	    <th >Regd</th>
       
		 <th >Un-registered</th>

		 <th >Regd</th>
       
		 <th >Un-registered</th>
		  <th >Regd</th>
       
		 <th >Un-registered</th>
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $frequency=$squan->frequency;
	          if($frequency=='7')
	          $frequency='more than six times';
			  $not_defence_reg=$squan->not_defence_reg;
			  $not_defence_unreg=$squan->not_defence_unreg;
              $defence_reg=$squan->defence_reg;

              $defence_unreg=$squan->defence_unreg;

              $total_reg=$squan->total_reg;
              $total_unreg=$squan->total_unreg;
              
              
			   //$bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';
      
		$bb=$base_root.$base_path.'admin/annual-report-taba-partc-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);


		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t($img),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output1 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$frequency."</td>";
			    $output1.= "<td>".$not_defence_reg."</td>";
                $output1.= "<td>".$not_defence_unreg."</td>";
                $output1.= "<td>".$defence_reg."</td>";
                $output1.= "<td>".$defence_unreg."</td>";
                $output1.= "<td>".$total_reg."</td>";
                $output1.= "<td>".$total_unreg."</td>";
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table>"; 
			  
			

	
	   



	  }
  catch (Exception $e) {
    //$form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output1 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output1;
		                 // exit;
                          
                          }



   function stpe1_tabc_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t1_c')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }                        



  function annual_report_step1_submit($form , $form_state) {	


         global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);  
//exit;
 
  $annual_inspection_id=trim($val['inspectionid']);  

  $Gfone=trim($val['Gfone']);  if(!$Gfone) $Gfone= NULL;         
  $Gftwo=trim($val['Gftwo']); if(!$Gftwo) $Gftwo= NULL;
  $Gfthree=trim($val['Gfthree']); if(!$Gfthree) $Gfthree= NULL;
  $Gffour=trim($val['Gffour']); if(!$Gffour) $Gffour= NULL;
  $Gffive=trim($val['Gffive']); if(!$Gffive) $Gffive= NULL;
  $Gfsix=trim($val['Gfsix']);   if(!$Gfsix) $Gfsix= NULL;
  $Gfseven=trim($val['Gfseven']); if(!$Gfseven) $Gfseven= NULL;
  $Gfeight=trim($val['Gfeight']); if(!$Gfeight) $Gfeight= NULL;



  $GfoneB=trim($val['GfoneB']);  if(!$GfoneB) $GfoneB= NULL;         
  $GftwoB=trim($val['GftwoB']); if(!$GftwoB) $GftwoB= NULL;
  $GfthreeB=trim($val['GfthreeB']); if(!$GfthreeB) $GfthreeB= NULL;
  $GffourB=trim($val['GffourB']); if(!$GffourB) $GffourB= NULL;
  $GffiveB=trim($val['GffiveB']); if(!$GffiveB) $GffiveB= NULL;
  $GfsixB=trim($val['GfsixB']);   if(!$GfsixB) $GfsixB= NULL;
  $GfsevenB=trim($val['GfsevenB']); if(!$GfsevenB) $GfsevenB= NULL;
  $GfeightddB=trim($val['GfeightddB']); if(!$GfeightddB) $GfeightddB= NULL;






  $Hfone=trim($val['Hfone']);  if(!$Hfone) $Hfone= NULL;         
  $Hftwo=trim($val['Hftwo']); if(!$Hftwo) $Hftwo= NULL;
  $Hfthree=trim($val['Hfthree']); if(!$Hfthree) $Hfthree= NULL;
  $Hffour=trim($val['Hffour']); if(!$Hffour) $Hffour= NULL;
  $Hffive=trim($val['Hffive']); if(!$Hffive) $Hffive= NULL;
  $Hfsix=trim($val['Hfsix']);   if(!$Hfsix) $Hfsix= NULL;
  $Hfseven=trim($val['Hfseven']); if(!$Hfseven) $Hfseven= NULL;
  $Hfeight=trim($val['Hfeight']); if(!$Hfeight) $Hfeight= NULL;


  $HfoneB=trim($val['HfoneB']);  if(!$HfoneB) $HfoneB= NULL;         
  $HftwoB=trim($val['HftwoB']); if(!$HftwoB) $HftwoB= NULL;
  $HfthreeB=trim($val['HfthreeB']); if(!$HfthreeB) $HfthreeB= NULL;
  $HffourB=trim($val['HffourB']); if(!$HffourB) $HffourB= NULL;
  $HffiveB=trim($val['HffiveB']); if(!$HffiveB) $HffiveB= NULL;
  $HfsixB=trim($val['HfsixB']);   if(!$HfsixB) $HfsixB= NULL;
  $HfsevenB=trim($val['HfsevenB']); if(!$HfsevenB) $HfsevenB= NULL;
  $HfeightB=trim($val['HfeightB']); if(!$HfeightB) $HfeightB= NULL;




  $MAHfone=trim($val['MAHfone']);  if(!$MAHfone) $MAHfone= NULL;         
  $MAHftwo=trim($val['MAHftwo']); if(!$MAHftwo) $MAHftwo= NULL;
  $MAHfthree=trim($val['MAHfthree']); if(!$MAHfthree) $MAHfthree= NULL;
  $MAHffour=trim($val['MAHffour']); if(!$MAHffour) $MAHffour= NULL;
  $MAHffive=trim($val['MAHffive']); if(!$MAHffive) $MAHffive= NULL;
  $MAHfsix=trim($val['MAHfsix']);   if(!$MAHfsix) $MAHfsix= NULL;
  $MAHfseven=trim($val['MAHfseven']); if(!$MAHfseven) $MAHfseven= NULL;
  $MAHfeight=trim($val['MAHfeight']); if(!$MAHfeight) $MAHfeight= NULL;



  $MAHfoneB=trim($val['MAHfoneB']);  if(!$MAHfoneB) $MAHfoneB= NULL;         
  $MAHftwoB=trim($val['MAHftwoB']); if(!$MAHftwoB) $MAHftwoB= NULL;
  $MAHfthreeB=trim($val['MAHfthreeB']); if(!$MAHfthreeB) $MAHfthreeB= NULL;
  $MAHffourB=trim($val['MAHffourB']); if(!$MAHffourB) $MAHffourB= NULL;
  $MAHffiveB=trim($val['MAHffiveB']); if(!$MAHffiveB) $MAHffiveB= NULL;
  $MAHfsixB=trim($val['MAHfsixB']);   if(!$MAHfsixB) $MAHfsixB= NULL;
  $MAHfsevenB=trim($val['MAHfsevenB']); if(!$MAHfsevenB) $MAHfsevenB= NULL;
  $MAHfeightB=trim($val['MAHfeightB']); if(!$MAHfeightB) $MAHfeightB= NULL;


  $misval=trim($val['misval']);  if(!$misval) $misval= NULL;
  $pwdval=trim($val['pwdval']);  if(!$pwdval) $pwdval= NULL;         
  $mbaval=trim($val['mbaval']); if(!$mbaval) $mbaval= NULL;
  $carval=trim($val['carval']); if(!$carval) $carval= NULL;
  $cival=trim($val['cival']); if(!$cival) $cival= NULL;
  $drival=trim($val['drival']); if(!$drival) $drival= NULL;
  $balhval=trim($val['balhval']);   if(!$balhval) $balhval= NULL;

  $oshhval=trim($val['oshhval']);   if(!$oshhval) $oshhval= NULL;

  //print $drival.'|'.$balhval.'|'.$oshhval;
  //exit;
  $faopval=trim($val['faopval']);   if(!$faopval) $faopval= NULL;
  $frolval=trim($val['frolval']);   if(!$frolval) $frolval= NULL;



  $colD12val=trim($val['colD12val']);  if(!$colD12val) $colD12val= NULL;         
  $colD13val=trim($val['colD13val']); if(!$colD13val) $colD13val= NULL;
  $colD14val=trim($val['colD14val']); if(!$colD14val) $colD14val= NULL;
  $colD15val=trim($val['colD15val']); if(!$colD15val) $colD15val= NULL;
  $colD16val=trim($val['colD16val']); if(!$colD16val) $colD16val= NULL;
  $colD17val=trim($val['colD17val']); if(!$colD17val) $colD17val= NULL;
  



   







  
    
    $txn = db_transaction();
	  try {


              $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_t1_a_b where  annual_inspection_id = :filenumber', array(':filenumber' => $annual_inspection_id));


              $query_update_b_yes=db_query('select  * from labour_factory_statcell_annual_report_t1_d where  annual_inspection_id = :filenumber', array(':filenumber' => $annual_inspection_id));
		
	     if($query_update_a_yes->rowCount() > 0 &&  $query_update_b_yes->rowCount() > 0) 
          {

           



        $query_update_A = db_update('labour_factory_statcell_annual_report_t1_a_b');
        $query_update_A->fields(array(
		  'g_nouv_regfac_2m_i' =>$Gfone,'g_nouv_regfac_2m_ii' =>$Gftwo, 'g_nouv_regfac_85' => $Gfthree, 'g_nouv_unregfac_2m_i' => $Gffour, 'g_nouv_unregfac_2m_ii' => $Gffive, 'g_nouv_unregfac_85' => $Gfsix, 'g_nouv_non_amendable' => $Gfseven, 'g_nouv_total' => $Gfeight,


    'g_novp_regfac_2m_i' => $GfoneB, 'g_novp_regfac_2m_ii' => $GftwoB , 'g_novp_regfac_85' => $GfthreeB
 	, 'g_novp_unregfac_2m_i' => $GffourB , 'g_novp_unregfac_2m_ii' => $GffiveB , 'g_novp_unregfac_85' => $GfsixB ,

 	'g_novp_non_amendable' => $GfsevenB , 'g_novp_total' => $GfeightddB,



 	'h_nouv_regfac_2m_i' => $Hfone, 'h_nouv_regfac_2m_ii' => $Hftwo , 'h_nouv_regfac_85' => $Hfthree
 	, 'h_nouv_unregfac_2m_i' => $Hffour , 'h_nouv_unregfac_2m_ii' => $Hffive , 'h_nouv_unregfac_85' => $Hfsix ,

 	'h_nouv_non_amendable' => $Hfseven , 'h_nouv_total' => $Hfeight,



 	'h_novp_regfac_2m_i' => $HfoneB, 'h_novp_regfac_2m_ii' => $HftwoB , 'h_novp_regfac_85' => $HfthreeB
 	, 'h_novp_unregfac_2m_i' => $HffourB , 'h_novp_unregfac_2m_ii' => $HffiveB , 'h_novp_unregfac_85' => $HfsixB ,

 	'h_novp_non_amendable' => $HfsevenB , 'h_novp_total' => $HfeightB,


 	'mah_nouv_regfac_2m_i' => $MAHfone, 'mah_nouv_regfac_2m_ii' => $MAHftwo , 'mah_nouv_regfac_85' => $MAHfthree
 	, 'mah_nouv_unregfac_2m_i' => $MAHffour , 'mah_nouv_unregfac_2m_ii' => $MAHffive , 'mah_nouv_unregfac_85' => $MAHfsix ,

 	'mah_nouv_non_amendable' => $MAHfseven , 'mah_nouv_total' => $MAHfeight,


 	'mah_novp_regfac_2m_i' => $MAHfoneB, 'mah_novp_regfac_2m_ii' => $MAHftwoB , 'mah_novp_regfac_85' => $MAHfthreeB
 	, 'mah_novp_unregfac_2m_i' => $MAHffourB , 'mah_novp_unregfac_2m_ii' => $MAHffiveB , 'mah_novp_unregfac_85' => $MAHfsixB ,

 	'mah_novp_non_amendable' => $MAHfsevenB , 'mah_novp_total' => $MAHfeightB






 	 ));
										
										
										
       $query_update_A->condition('annual_inspection_id',$annual_inspection_id);
       $query_update_A->execute();



      $query_update_B = db_update('labour_factory_statcell_annual_report_t1_d');
      $query_update_B->fields(array(
		   'visit_msihcr' =>$misval,'visit_pwa' =>$pwdval, 'visit_mba' => $mbaval, 'visit_car' => $carval, 'visit_clpra' => $cival, 'visit_rest_interval' => $drival, 'visit_bef_after_legal_hours' => $balhval, 'visit_sunday_holiday' => $oshhval,


    'visit_approval_of_plan' => $faopval, 'visit_renew_licence' => $frolval , 'visit_collection_statistics' => $colD12val
 	, 'visit_enq_complaints' => $colD13val , 'visit_court_prosecution' => $colD14val , 'visit_to_closed_factory' => $colD15val ,

 	'visit_others' => $colD16val , 'visit_total' => $colD17val ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$annual_inspection_id);
       $query_update_B->execute(); 






          }
          else

          {

  
            $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t1_a_b');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $rowid=$querystring;

 $fieldsA = array('row_id' => $rowid ,'annual_inspection_id' => $annual_inspection_id, 'g_nouv_regfac_2m_i' =>$Gfone,'g_nouv_regfac_2m_ii' =>$Gftwo, 'g_nouv_regfac_85' => $Gfthree, 'g_nouv_unregfac_2m_i' => $Gffour, 'g_nouv_unregfac_2m_ii' => $Gffive, 'g_nouv_unregfac_85' => $Gfsix, 'g_nouv_non_amendable' => $Gfseven, 'g_nouv_total' => $Gfeight,


    'g_novp_regfac_2m_i' => $GfoneB, 'g_novp_regfac_2m_ii' => $GftwoB , 'g_novp_regfac_85' => $GfthreeB
 	, 'g_novp_unregfac_2m_i' => $GffourB , 'g_novp_unregfac_2m_ii' => $GffiveB , 'g_novp_unregfac_85' => $GfsixB ,

 	'g_novp_non_amendable' => $GfsevenB , 'g_novp_total' => $GfeightddB,


   


 	'h_nouv_regfac_2m_i' => $Hfone, 'h_nouv_regfac_2m_ii' => $Hftwo , 'h_nouv_regfac_85' => $Hfthree
 	, 'h_nouv_unregfac_2m_i' => $Hffour , 'h_nouv_unregfac_2m_ii' => $Hffive , 'h_nouv_unregfac_85' => $Hfsix ,

 	'h_nouv_non_amendable' => $Hfseven , 'h_nouv_total' => $Hfeight,



 	'h_novp_regfac_2m_i' => $HfoneB, 'h_novp_regfac_2m_ii' => $HftwoB , 'h_novp_regfac_85' => $HfthreeB
 	, 'h_novp_unregfac_2m_i' => $HffourB , 'h_novp_unregfac_2m_ii' => $HffiveB , 'h_novp_unregfac_85' => $HfsixB ,

 	'h_novp_non_amendable' => $HfsevenB , 'h_novp_total' => $HfeightB,


 	'mah_nouv_regfac_2m_i' => $MAHfone, 'mah_nouv_regfac_2m_ii' => $MAHftwo , 'mah_nouv_regfac_85' => $MAHfthree
 	, 'mah_nouv_unregfac_2m_i' => $MAHffour , 'mah_nouv_unregfac_2m_ii' => $MAHffive , 'mah_nouv_unregfac_85' => $MAHfsix ,

 	'mah_nouv_non_amendable' => $MAHfseven , 'mah_nouv_total' => $MAHfeight,


 	'mah_novp_regfac_2m_i' => $MAHfoneB, 'mah_novp_regfac_2m_ii' => $MAHftwoB , 'mah_novp_regfac_85' => $MAHfthreeB
 	, 'mah_novp_unregfac_2m_i' => $MAHffourB , 'mah_novp_unregfac_2m_ii' => $MAHffiveB , 'mah_novp_unregfac_85' => $MAHfsixB ,

 	'mah_novp_non_amendable' => $MAHfsevenB , 'mah_novp_total' => $MAHfeightB,


    );
		  
db_insert('labour_factory_statcell_annual_report_t1_a_b')->fields($fieldsA)->execute();	




   $fieldsB = array('row_id' => $rowid ,'annual_inspection_id' => $annual_inspection_id, 'visit_msihcr' =>$misval,'visit_pwa' =>$pwdval, 'visit_mba' => $mbaval, 'visit_car' => $carval, 'visit_clpra' => $cival, 'visit_rest_interval' => $drival, 'visit_bef_after_legal_hours' => $balhval, 'visit_sunday_holiday' => $oshhval,


    'visit_approval_of_plan' => $faopval, 'visit_renew_licence' => $frolval , 'visit_collection_statistics' => $colD12val
 	, 'visit_enq_complaints' => $colD13val , 'visit_court_prosecution' => $colD14val , 'visit_to_closed_factory' => $colD15val ,

 	'visit_others' => $colD16val , 'visit_total' => $colD17val,


         );
		  
db_insert('labour_factory_statcell_annual_report_t1_d')->fields($fieldsB)->execute();	

 }


	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
                $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				  $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$annual_inspection_id);
	           
	              //drupal_set_message(t($message));
	              drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$annual_inspection_id);

             $message = 'DATA NOT SAVED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }
	
		 
		 
	
	 	}
		
		
 
		
				
	
														
														  
	       