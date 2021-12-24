
<?php

function annual_report_list( $form, &$form_state , $filenumber= NULL  ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	    $uid	=	$user->uid; 

	    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

	  // $uid	='23565';

	  // print "sssssssssss".$uid;

	    $report_from_date=NULL;
       $report_to_date=NULL;
       $annual_form_type=NULL;

       $area=NULL;
       $area_id=NULL;

	    if(trim($filenumber)){

	 $annual_rep_edit_query = db_select('labour_factory_statcell_annual_report', 'p');
	 $annual_rep_edit_query->fields('p',array('annual_inspection_id','inspector_id','report_from_date','report_to_date',
	'report_year','annual_form_type','status','submit_date','area','e_note','create_date','create_by','is_submitted','remarks','accept_by','area_id'));
	 $annual_rep_edit_query->condition('p.annual_inspection_id',trim($filenumber),'=');
	 $anrEdit_result = $annual_rep_edit_query->execute(); 

	   $result_anrEdit=$anrEdit_result->fetchAssoc();
       $report_from_date=$result_anrEdit['report_from_date'];
       $report_to_date=$result_anrEdit['report_to_date'];
       $annual_form_type=$result_anrEdit['annual_form_type'];

       $area=$result_anrEdit['area'];
       $area_id=$result_anrEdit['area_id'];

	    }


$form['#attached']['js'] = array(drupal_get_path('module', 'annual_report') . '/js/annualreport.js',);	
   
      $thisYear = date("Y")-1;
           $form['annulreportfield'] = array(
          '#title' => t('Annual Report  : '.$thisYear.''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
   $form['annulreportfield']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );
 $form['annulreportfield']['annualReportid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
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
		
		  '#default_value' => !empty($annual_form_type) ? $annual_form_type : NULL , 
		
				
        
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
	             '#default_value' => !empty($report_from_date) ? date('d-m-Y', strtotime($report_from_date)) : NULL , 
	   
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
		           '#default_value' => !empty($report_to_date) ? date('d-m-Y', strtotime($report_to_date)) : NULL , 
	   
	   
           ); 

           $options_zone = array(0 => " Select  ") + anr_zone_option();
          $user_zone=explode(",",$area_id)  ;
          $form['annulreportfield']['anr_zone'] = array (
                    '#type' => 'select',
                    '#title' => ('Zone'),
				    '#options' 		 => $options_zone,
			    	
		            '#required' => TRUE,
					 '#multiple'     =>  true,
					  '#attributes' => array('style' => array('height: 100px;')),
				
	               '#prefix' 		 	=> '<div class="col-md-3"> ',
	               '#suffix' 		 	=> '</div>',
	                '#rows'        => 10,
	              '#default_value' => array_values($user_zone) ,  
               );
	   
	   
	     if(trim($filenumber)){

	$form['annulreportfield']['submit_button']	= array(
																 
                                                               '#prefix' => '<div style="text-align:right;" class="col-sm-12" >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
															    '#value'				=>t(' Update & Next '),
																'#element_validate' => array('annual_report_validate'),
																);

	     }

	     else
	     {
	   
          	$form['annulreportfield']['submit_button']	= array(
																 
                                                               '#prefix' => '<div style="text-align:right;" class="col-sm-12" >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Next '),
																'#element_validate' => array('annual_report_validate'),
																);
		 
	   }
	  
		 
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

            $kk=$base_root.$base_path.'admin/annual-report-list/'.encryption_decryption_fun('encrypt',$data->annual_inspection_id);
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
    $from=date('Y-m-d', strtotime(trim($val['from'])));
    $to=date('Y-m-d', strtotime(trim($val['to'])));
    $annualReportid=trim($val['annualReportid']);

    //print $uid.'='.$from.'='.$to;
    //exit;
   if($annualReportid){

   	 $ann_report=db_query('select  * from labour_factory_statcell_annual_report where  inspector_id=:filenumber and report_from_date=:fdt and report_to_date=:tdt and annual_inspection_id != :anrid', array(':filenumber' => $uid , ':fdt' => $from , ':tdt' => $to, ':anrid' => $annualReportid) );
		
	      if($ann_report->rowCount() > 0) 
          { 
	  
	 
	  form_error($element, t(' Annual report already exist  . '));
	 
		 
	   
          
		 }

     }
     else
     {
     $ann_report=db_query('select  * from labour_factory_statcell_annual_report where  inspector_id=:filenumber and report_from_date=:fdt and report_to_date=:tdt', array(':filenumber' => $uid , ':fdt' => $from , ':tdt' => $to) );
		
	      if($ann_report->rowCount() > 0) 
          { 
	  
	 
	  form_error($element, t(' Annual report already exist  . '));
	 
		 
	   
          
		 }

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

   
     $annualReportid=trim($val['annualReportid']);
    $annual_report=trim($val['annual_report']);
	$uid=trim($val['uid']);
	//$from=trim($val['from']);
	//$to=trim($val['to']);
	$from="2021-01-01";//"2021-04-01";//"2021-01-01";//date('Y-m-d', strtotime(trim($val['from'])));
    $to="2021-12-31";//"2022-03-31";//"2021-12-31";//date('Y-m-d', strtotime(trim($val['to'])));
	$thisYear = "2021";//date("Y")-1;

	$previous_year="2020";//$thisYear - 1;

	if($annual_report=='CALENDAR'){
		$previous_from_year_dt='1900-01-01';
	    $previous_to_year_dt=$previous_year.'-12-31';
	}
	elseif($annual_report=='FINANCIAL'){
		$previous_from_year_dt='1900-01-01';
	    $previous_to_year_dt="2022-03-31";//date("Y")."-03-31";
	}

   
   //print $thisYear."==".$from."==".$to."==".$thisYear;
   //exit;


	

	$zone = array_filter($form_state['values']['anr_zone']);
	//print print_r($zone);
	//exit;

 $txn = db_transaction();
	  try {
            

                 if($annualReportid){



                   $ann_report_cal_fin_year=db_query('select  * from labour_factory_statcell_annual_report where  inspector_id=:filenumber and report_from_date=:fdt and report_to_date=:tdt and annual_inspection_id = :aiid and ( annual_form_type = :afty or annual_form_type = :aftf )', array(':filenumber' => $uid , ':fdt' => $from , ':tdt' => $to, ':aiid' => $annualReportid , ':afty' => 'CALENDAR', ':aftf' => 'FINANCIAL') );
		
	      if($ann_report_cal_fin_year->rowCount() > 0)  // same calender or fin year
          { 

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


      $query_update_A = db_update('labour_factory_statcell_annual_report');
      $query_update_A->fields(array(
     'area' =>$area ,'area_id' => $area_id));
                    
                    
                    
       $query_update_A->condition('annual_inspection_id',$annualReportid);
       $query_update_A->execute();

           $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$annualReportid);
	           
	             drupal_goto($full_base);

          }



        elseif($ann_report_cal_fin_year->rowCount() == 0)  // not same calender or fin year
          {






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


      $query_update_A = db_update('labour_factory_statcell_annual_report');
      $query_update_A->fields(array(
       'annual_form_type' => $annual_report, 'report_from_date' =>$from, 'report_to_date' => $to ,'area' =>$area ,'area_id' => $area_id, 'report_year' => $thisYear));
                    
                    
                    
       $query_update_A->condition('annual_inspection_id',$annualReportid);
       $query_update_A->execute();


      
         /* 1.   update  step1 a , b   */

           $step1_mr_select_query = db_select('labour_factory_statcell_form_5_6_7_t1', 'a');

           $step1_mr_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
          $step1_mr_select_query->condition('b.inspector_id',trim($uid),'=');
          $step1_mr_select_query->condition('b.report_from_date',trim($from),'>=');
          $step1_mr_select_query->condition('b.report_to_date',trim($to),'<=');
          $step1_mr_select_query->condition('b.status','FS','='); 


          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_2m_i),0)', 'g_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_2m_ii),0)', 'g_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_85),0)', 'g_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_2m_i),0)', 'g_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_2m_ii),0)', 'g_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_85),0)', 'g_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_non_amendable),0)', 'g_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_total),0)', 'g_nouv_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_2m_i),0)', 'g_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_2m_ii),0)', 'g_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_85),0)', 'g_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_2m_i),0)', 'g_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_2m_ii),0)', 'g_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_85),0)', 'g_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_non_amendable),0)', 'g_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_total),0)', 'g_novp_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_2m_i),0)', 'h_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_2m_ii),0)', 'h_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_85),0)', 'h_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_2m_i),0)', 'h_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_2m_ii),0)', 'h_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_85),0)', 'h_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_non_amendable),0)', 'h_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_total),0)', 'h_nouv_total');

          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_2m_i),0)', 'h_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_2m_ii),0)', 'h_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_85),0)', 'h_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_2m_i),0)', 'h_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_2m_ii),0)', 'h_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_85),0)', 'h_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_non_amendable),0)', 'h_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_total),0)', 'h_novp_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_2m_i),0)', 'mah_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_2m_ii),0)', 'mah_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_85),0)', 'mah_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_2m_i),0)', 'mah_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_2m_ii),0)', 'mah_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_85),0)', 'mah_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_non_amendable),0)', 'mah_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_total),0)', 'mah_nouv_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_2m_i),0)', 'mah_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_2m_ii),0)', 'mah_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_85),0)', 'mah_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_2m_i),0)', 'mah_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_2m_ii),0)', 'mah_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_85),0)', 'mah_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_non_amendable),0)', 'mah_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_total),0)', 'mah_novp_total');



		
       

         

        $step1_mr_select_query_result = $step1_mr_select_query->execute(); 


		
		$result_step1_A=$step1_mr_select_query_result->fetchAssoc();

		//print_r($result_step1_A);
         //exit;

		$g_nouv_regfac_2m_i=$result_step1_A['g_nouv_regfac_2m_i'];


		$g_nouv_regfac_2m_ii=$result_step1_A['g_nouv_regfac_2m_ii'];

		$g_nouv_regfac_85=$result_step1_A['g_nouv_regfac_85'];
		
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



     










       $query_update_step1_AB = db_update('labour_factory_statcell_annual_report_t1_a_b');
       $query_update_step1_AB->fields(array(
        'g_nouv_regfac_2m_i' =>$g_nouv_regfac_2m_i,'g_nouv_regfac_2m_ii' =>$g_nouv_regfac_2m_ii, 'g_nouv_regfac_85' => $g_nouv_regfac_85, 'g_nouv_unregfac_2m_i' => $g_nouv_unregfac_2m_i, 'g_nouv_unregfac_2m_ii' => $g_nouv_unregfac_2m_ii, 'g_nouv_unregfac_85' => $g_nouv_unregfac_85, 'g_nouv_non_amendable' => $g_nouv_non_amendable, 'g_nouv_total' => $g_nouv_total,


    'g_novp_regfac_2m_i' => $g_novp_regfac_2m_i, 'g_novp_regfac_2m_ii' => $g_novp_regfac_2m_ii , 'g_novp_regfac_85' => $g_novp_regfac_85
 	, 'g_novp_unregfac_2m_i' => $g_novp_unregfac_2m_i , 'g_novp_unregfac_2m_ii' => $g_novp_unregfac_2m_ii , 'g_novp_unregfac_85' => $g_novp_unregfac_85 ,

 	'g_novp_non_amendable' => $g_novp_non_amendable , 'g_novp_total' => $g_novp_total,


   


 	'h_nouv_regfac_2m_i' => $h_nouv_regfac_2m_i, 'h_nouv_regfac_2m_ii' => $h_nouv_regfac_2m_ii , 'h_nouv_regfac_85' => $h_nouv_regfac_85
 	, 'h_nouv_unregfac_2m_i' => $h_nouv_unregfac_2m_i , 'h_nouv_unregfac_2m_ii' => $h_nouv_unregfac_2m_ii , 'h_nouv_unregfac_85' => $h_nouv_unregfac_85 ,

 	'h_nouv_non_amendable' => $h_nouv_non_amendable , 'h_nouv_total' => $h_nouv_total,



 	'h_novp_regfac_2m_i' => $h_novp_regfac_2m_i, 'h_novp_regfac_2m_ii' => $h_novp_regfac_2m_ii , 'h_novp_regfac_85' => $h_novp_regfac_85
 	, 'h_novp_unregfac_2m_i' => $h_novp_unregfac_2m_i , 'h_novp_unregfac_2m_ii' => $h_novp_unregfac_2m_ii , 'h_novp_unregfac_85' => $h_novp_unregfac_85 ,

 	'h_novp_non_amendable' => $h_novp_non_amendable , 'h_novp_total' => $h_novp_total,


 	'mah_nouv_regfac_2m_i' => $mah_nouv_regfac_2m_i, 'mah_nouv_regfac_2m_ii' => $mah_nouv_regfac_2m_ii , 'mah_nouv_regfac_85' => $mah_nouv_regfac_85
 	, 'mah_nouv_unregfac_2m_i' => $mah_nouv_unregfac_2m_i , 'mah_nouv_unregfac_2m_ii' => $mah_nouv_unregfac_2m_ii , 'mah_nouv_unregfac_85' => $mah_nouv_unregfac_85 ,

 	'mah_nouv_non_amendable' => $mah_nouv_non_amendable , 'mah_nouv_total' => $mah_nouv_total,


 	'mah_novp_regfac_2m_i' => $mah_novp_regfac_2m_i, 'mah_novp_regfac_2m_ii' => $mah_novp_regfac_2m_ii , 'mah_novp_regfac_85' => $mah_novp_regfac_85
 	, 'mah_novp_unregfac_2m_i' => $mah_novp_unregfac_2m_i , 'mah_novp_unregfac_2m_ii' => $mah_novp_unregfac_2m_ii , 'mah_novp_unregfac_85' => $mah_novp_unregfac_85 ,

 	'mah_novp_non_amendable' => $mah_novp_non_amendable , 'mah_novp_total' => $mah_novp_total ));
                    
                    
                    
       $query_update_step1_AB->condition('annual_inspection_id',$annualReportid);
      
       $query_update_step1_AB->execute(); 
       

       /* end   update  step1 a , b    */ 

          
              /*   */



                    /* 2.    step 1  D    No. of Visits paid Update    */


                     $mr_specialVisit_select_query = db_select('labour_factory_statcell_form_5_6_7_t2', 'a');

                     $mr_specialVisit_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                     $mr_specialVisit_select_query->condition('b.inspector_id',trim($uid),'=');
                     $mr_specialVisit_select_query->condition('b.report_from_date',trim($from),'>=');
                     $mr_specialVisit_select_query->condition('b.report_to_date',trim($to),'<=');
                     $mr_specialVisit_select_query->condition('b.status','FS','=');
       
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_pwa),0)', 'visit_pwa');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_mba),0)', 'visit_mba');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_msihcr),0)', 'visit_msihcr');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_car),0)', 'visit_car');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_clpra),0)', 'visit_clpra');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_rest_interval),0)', 'visit_rest_interval');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_bef_after_legal_hours),0)', 'visit_bef_after_legal_hours');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_sunday_holiday),0)', 'visit_sunday_holiday');

                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_approval_of_plan),0)', 'visit_approval_of_plan');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_reg_licence),0)', 'visit_reg_licence');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_collection_statistics),0)', 'visit_collection_statistics');
                 $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_enq_complaints),0)', 'visit_enq_complaints');
                 $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_court_attendance),0)', 'visit_court_attendance');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_attn_seminar_meeting),0)', 'visit_attn_seminar_meeting');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_to_closed_factory),0)', 'visit_to_closed_factory');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_others),0)', 'visit_others');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_total),0)', 'visit_total');


               
                $mr_specialVisit_select_query_result = $mr_specialVisit_select_query->execute(); 
    
               $result_specialVisit=$mr_specialVisit_select_query_result->fetchAssoc();

               $visit_pwa=$result_specialVisit['visit_pwa'];
               $visit_mba=$result_specialVisit['visit_mba'];
               $visit_msihcr=$result_specialVisit['visit_msihcr'];
               $visit_car=$result_specialVisit['visit_car'];

               $visit_clpra=$result_specialVisit['visit_clpra'];
               $visit_rest_interval=$result_specialVisit['visit_rest_interval'];
               $visit_bef_after_legal_hours=$result_specialVisit['visit_bef_after_legal_hours'];
               $visit_sunday_holiday=$result_specialVisit['visit_sunday_holiday'];

               $visit_approval_of_plan=$result_specialVisit['visit_approval_of_plan'];
               $visit_reg_licence=$result_specialVisit['visit_reg_licence'];


               $visit_collection_statistics=$result_specialVisit['visit_collection_statistics'];
               $visit_enq_complaints=$result_specialVisit['visit_enq_complaints'];

               $visit_court_attendance=$result_specialVisit['visit_court_attendance'];
               $visit_attn_seminar_meeting=$result_specialVisit['visit_attn_seminar_meeting']; // not add annual report
               $visit_to_closed_factory=$result_specialVisit['visit_to_closed_factory'];
               $visit_others=$result_specialVisit['visit_others'];
               $visit_total=$result_specialVisit['visit_total'];






       $query_update_step1_D = db_update('labour_factory_statcell_annual_report_t1_d');
       $query_update_step1_D->fields(array(
      'visit_msihcr' =>$visit_msihcr,'visit_pwa' =>$visit_pwa, 'visit_mba' => $visit_mba, 'visit_car' => $visit_car, 'visit_clpra' => $visit_clpra, 'visit_rest_interval' => $visit_rest_interval, 'visit_bef_after_legal_hours' => $visit_bef_after_legal_hours, 'visit_sunday_holiday' => $visit_sunday_holiday,


    'visit_approval_of_plan' => $visit_approval_of_plan, 'visit_renew_licence' => $visit_reg_licence , 'visit_collection_statistics' => $visit_collection_statistics
 	, 'visit_enq_complaints' => $visit_enq_complaints , 'visit_court_prosecution' => $visit_court_attendance , 'visit_to_closed_factory' => $visit_to_closed_factory ,'visit_others' => $visit_others , 'visit_total' => ($visit_total - $visit_attn_seminar_meeting )));
                    
       $query_update_step1_D->condition('annual_inspection_id',$annualReportid);
      
       $query_update_step1_D->execute();           
                    
    
      
               

       
		  
          /*     end step 1  D    No. of Visits paid Update    */



          /* Update step 2 part a accident and dangerous occurance     */

        $mr_ado_select_query = db_select('labour_factory_statcell_form_5_t3', 'a');
       
       $mr_ado_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
       $mr_ado_select_query->condition('b.inspector_id',trim($uid),'=');
       $mr_ado_select_query->condition('b.report_from_date',trim($from),'>=');
       $mr_ado_select_query->condition('b.report_to_date',trim($to),'<=');
       $mr_ado_select_query->condition('b.status','FS','=');

        $mr_ado_select_query->addExpression('COALESCE(sum(no_fatal),0)', 'no_fatal');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_serious),0)', 'no_serious');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_explosion),0)', 'no_explosion');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_fire),0)', 'no_fire');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_gassing),0)', 'no_gassing');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_toxic_release),0)', 'no_toxic_release');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_collapse),0)', 'no_collapse');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_others),0)', 'no_others');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_fatal),0)', 'visit_fatal');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_serious),0)', 'visit_serious');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_explosion),0)', 'visit_explosion');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_fire),0)', 'visit_fire');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_gassing),0)', 'visit_gassing');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_toxic_release),0)', 'visit_toxic_release');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_collapse),0)', 'visit_collapse');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_others),0)', 'visit_others');

     
      
		
       
        $mr_ado_select_query_result = $mr_ado_select_query->execute(); 
		
		$result_mrado=$mr_ado_select_query_result->fetchAssoc();
		$ado_no_of_accidents_fatal=$result_mrado['no_fatal'];
        $ado_no_of_accidents_serious=$result_mrado['no_serious'];
        $no_fire=$result_mrado['no_fire'];
        $no_explosion=$result_mrado['no_explosion'];
        $ado_no_danger_occur_gassing=$result_mrado['no_gassing'];
		
		$ado_no_danger_occur_toxic_release=$result_mrado['no_toxic_release'];
		$ado_no_danger_occur_collapse=$result_mrado['no_collapse'];

		$ado_no_danger_occur_others=$result_mrado['no_others'];


	   $ado_no_visit_paid_fatal_accidents=$result_mrado['visit_fatal'];
       $visit_serious=$result_mrado['visit_serious'];
	   $visit_explosion=$result_mrado['visit_explosion'];
	   $visit_fire=$result_mrado['visit_fire'];
	   $ado_no_visit_paid_gassing=$result_mrado['visit_gassing'];
	   $ado_no_visit_paid_toxic_release=$result_mrado['visit_toxic_release'];
	   $ado_no_visit_paid_collapse=$result_mrado['visit_collapse'];
	   $ado_no_visit_paid_others=$result_mrado['visit_others'];


	       




      $query_update_step2_A = db_update('labour_factory_statcell_annual_report_t2_a');
      $query_update_step2_A->fields(array(
       'ado_no_of_accidents_fatal' =>$ado_no_of_accidents_fatal, 'ado_no_of_accidents_serious' => $ado_no_of_accidents_serious, 'ado_no_danger_occur_explosion' => $no_explosion, 'ado_no_danger_occur_fire' => $no_fire, 'ado_no_danger_occur_gassing' => $ado_no_danger_occur_gassing, 'ado_no_danger_occur_toxic_release' => $ado_no_danger_occur_toxic_release, 'ado_no_danger_occur_collapse' => $ado_no_danger_occur_collapse, 'ado_no_danger_occur_others' => $ado_no_danger_occur_others, 'ado_no_visit_paid_fatal_accidents' => $ado_no_visit_paid_fatal_accidents, 'ado_no_visit_paid_serious_accidents' => $visit_serious, 'ado_no_visit_paid_explosion' => $visit_explosion, 'ado_no_visit_paid_fire' => $visit_fire, 'ado_no_visit_paid_gassing' => $ado_no_visit_paid_gassing,'ado_no_visit_paid_toxic_release' => $ado_no_visit_paid_toxic_release,'ado_no_visit_paid_collapse' => $ado_no_visit_paid_collapse,'ado_no_visit_paid_others' => $ado_no_visit_paid_others));
                    
                    
                    
       $query_update_step2_A->condition('annual_inspection_id',$annualReportid);
       $query_update_step2_A->execute();



          /* end Update step 2 part a accident and dangerous occurance     */


           /*  update  details of fatal & serious accident  */


                        db_delete('labour_factory_statcell_annual_report_t2_b')
                        ->condition('annual_inspection_id', $annualReportid)
                        ->execute();
                       
  


                          $mr_det_fatal_serious_select_query = db_select('labour_factory_statcell_form_5_t4a', 'a');
       
                         $mr_det_fatal_serious_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_det_fatal_serious_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_det_fatal_serious_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_det_fatal_serious_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_det_fatal_serious_select_query->condition('b.status','FS','=');

                          $mr_det_fatal_serious_select_query->fields('a',array('acc_det_name_of_factory','acc_det_address_of_factory',
        'acc_det_name_of_deceased_injured','acc_det_date_of_accident','classification_code'));

                         $mr_det_fatal_serious_select_query_result = $mr_det_fatal_serious_select_query->execute();

                     
                       if($mr_det_fatal_serious_select_query_result->rowCount() > 0) 
                       { 

                      foreach($mr_det_fatal_serious_select_query_result as $squan) {
                      


                


              $maxresult_t2b=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t2_b'); 
          $result_t2b=$maxresult_t2b->fetchAssoc();
          $max_sl_number_t2b = trim($result_t2b['maxsl']); 
            if($max_sl_number_t2b==0){$querystring_t2b=1; }else{ $querystring_t2b=$max_sl_number_t2b+1; }
          $rowid_t2b=$querystring_t2b;
           

                $fieldsE_t2_b = array('row_id' => $rowid_t2b, 'annual_inspection_id' => $annualReportid,'accident_type' =>'Serious' ,'acc_det_name_of_factory' =>trim($squan->acc_det_name_of_factory),'acc_det_address_of_factory' =>trim($squan->acc_det_address_of_factory), 'acc_det_name_of_deceased_injured' => trim($squan->acc_det_name_of_deceased_injured), 'acc_det_date_of_accident' => $squan->acc_det_date_of_accident,   'classification_code' => $squan->classification_code );
      
       
          db_insert('labour_factory_statcell_annual_report_t2_b')->fields($fieldsE_t2_b)->execute();  
       
          

       }
   }

   /*  end update  details of fatal & serious accident  */



    /*  start update orders issued under various act & rules */


                          db_delete('labour_factory_statcell_annual_report_t4')
                        ->condition('annual_inspection_id', $annualReportid)
                        ->execute();


                      
                         $mr_order_issue_act_rule_select_query = db_select('labour_factory_statcell_form_5_t7', 'a');
       
                         $mr_order_issue_act_rule_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_order_issue_act_rule_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_order_issue_act_rule_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_order_issue_act_rule_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_order_issue_act_rule_select_query->condition('b.status','FS','=');

                          $mr_order_issue_act_rule_select_query->fields('a',array('factory_name','factory_address',
        'acts_issued','time_allowed','result_description'));

                         $mr_order_issue_act_rule_select_query_result = $mr_order_issue_act_rule_select_query->execute();

                     
                       if($mr_order_issue_act_rule_select_query_result->rowCount() > 0) 
                       { 

                      foreach($mr_order_issue_act_rule_select_query_result as $squan) {

                         

                       

                           $maxresult_t4=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t4');	
	                       $result_t4=$maxresult_t4->fetchAssoc();
	                       $max_sl_number_t4 = trim($result_t4['maxsl']); 
                         if($max_sl_number_t4==0){$querystring_t4=1;	}else{ $querystring_t4=$max_sl_number_t4+1; }
		                  $rowid_t4=$querystring_t4;


		
	      
		   
		    $fieldsE_t4 = array('row_id' => $rowid_t4, 'annual_inspection_id' => $annualReportid,'factory_name' =>trim($squan->factory_name) ,'factory_address' =>trim($squan->factory_address),'section_rule_issued' =>trim($squan->acts_issued), 'time_allowed' => trim($squan->time_allowed), 'brief_description' => trim($squan->result_description));
		  
		   
           db_insert('labour_factory_statcell_annual_report_t4')->fields($fieldsE_t4)->execute();




                      }
                  }




                    /*  end update  orders issued under various act & rules */


          /* start update complaints */

                   $mr_complaints_select_query = db_select('labour_factory_statcell_form_5_t8', 'a');

                   $mr_complaints_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                   $mr_complaints_select_query->condition('b.inspector_id',trim($uid),'=');
                   $mr_complaints_select_query->condition('b.report_from_date',trim($from),'>=');
                   $mr_complaints_select_query->condition('b.report_to_date',trim($to),'<=');
                   $mr_complaints_select_query->condition('b.status','FS','=');
       
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_fa),0)', 'compl_reg_no_rec_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_pwa),0)', 'compl_reg_no_rec_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_mba),0)', 'compl_reg_no_rec_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_msihcr),0)', 'compl_reg_no_rec_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_car),0)', 'compl_reg_no_rec_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_clpra),0)', 'compl_reg_no_rec_clpra');

                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_fa),0)', 'compl_unreg_no_rec_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_pwa),0)', 'compl_unreg_no_rec_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_mba),0)', 'compl_unreg_no_rec_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_msihcr),0)', 'compl_unreg_no_rec_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_car),0)', 'compl_unreg_no_rec_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_clpra),0)', 'compl_unreg_no_rec_clpra');


                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_fa),0)', 'compl_reg_no_inv_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_pwa),0)', 'compl_reg_no_inv_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_mba),0)', 'compl_reg_no_inv_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_msihcr),0)', 'compl_reg_no_inv_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_car),0)', 'compl_reg_no_inv_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_clpra),0)', 'compl_reg_no_inv_clpra');

                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_fa),0)', 'compl_unreg_no_inv_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_pwa),0)', 'compl_unreg_no_inv_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_mba),0)', 'compl_unreg_no_inv_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_msihcr),0)', 'compl_unreg_no_inv_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_car),0)', 'compl_unreg_no_inv_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_clpra),0)', 'compl_unreg_no_inv_clpra');


                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_fa, ';')", "compl_reg_violation_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_pwa, ';')", "compl_reg_violation_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_mba, ';')", "compl_reg_violation_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_msihcr, ';')", "compl_reg_violation_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_car, ';')", "compl_reg_violation_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_clpra, ';')", "compl_reg_violation_clpra");

                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_fa, ';')", "compl_unreg_violation_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_pwa, ';')", "compl_unreg_violation_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_mba, ';')", "compl_unreg_violation_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_msihcr, ';')", "compl_unreg_violation_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_car, ';')", "compl_unreg_violation_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_clpra, ';')", "compl_unreg_violation_clpra");


                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_fa, ';')", "compl_reg_remarks_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_pwa, ';')", "compl_reg_remarks_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_mba, ';')", "compl_reg_remarks_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_msihcr, ';')", "compl_reg_remarks_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_car, ';')", "compl_reg_remarks_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_clpra, ';')", "compl_reg_remarks_clpra");

                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_fa, ';')", "compl_unreg_remarks_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_pwa, ';')", "compl_unreg_remarks_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_mba, ';')", "compl_unreg_remarks_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_msihcr, ';')", "compl_unreg_remarks_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_car, ';')", "compl_unreg_remarks_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_clpra, ';')", "compl_unreg_remarks_clpra");
        



               
                $mr_complaints_select_query_result = $mr_complaints_select_query->execute(); 
    
                $result_complaints=$mr_complaints_select_query_result->fetchAssoc();



               $reg_complaints_total_no = $result_complaints['compl_reg_no_rec_fa'] + $result_complaints['compl_reg_no_rec_pwa'] + $result_complaints['compl_reg_no_rec_mba'] + $result_complaints['compl_reg_no_rec_msihcr'] + $result_complaints['compl_reg_no_rec_car'] + $result_complaints['compl_reg_no_rec_clpra'];

               $unreg_complaints_total_no = $result_complaints['compl_unreg_no_rec_fa'] + $result_complaints['compl_unreg_no_rec_pwa'] + $result_complaints['compl_unreg_no_rec_mba'] + $result_complaints['compl_unreg_no_rec_msihcr'] + $result_complaints['compl_unreg_no_rec_car'] + $result_complaints['compl_unreg_no_rec_clpra'];

               $reg_complaints_total_inv = $result_complaints['compl_reg_no_inv_fa'] + $result_complaints['compl_reg_no_inv_pwa'] + $result_complaints['compl_reg_no_inv_mba'] + $result_complaints['compl_reg_no_inv_msihcr'] + $result_complaints['compl_reg_no_inv_car'] + $result_complaints['compl_reg_no_inv_clpra'];

               $unreg_complaints_total_inv = $result_complaints['compl_unreg_no_inv_fa'] + $result_complaints['compl_unreg_no_inv_pwa'] + $result_complaints['compl_unreg_no_inv_mba'] + $result_complaints['compl_unreg_no_inv_msihcr'] + $result_complaints['compl_unreg_no_inv_car'] + $result_complaints['compl_unreg_no_inv_clpra'];

               $reg_complaints_total_vio = $result_complaints['compl_reg_violation_fa'] + $result_complaints['compl_reg_violation_pwa'] + $result_complaints['compl_reg_violation_mba'] +
               $result_complaints['compl_reg_violation_msihcr'] + $result_complaints['compl_reg_violation_car'] + $result_complaints['compl_reg_violation_clpra'];

               $unreg_complaints_total_vio = $result_complaints['compl_unreg_violation_fa'] + $result_complaints['compl_unreg_violation_pwa'] + $result_complaints['compl_unreg_violation_mba'] +
                 + $result_complaints['compl_unreg_violation_msihcr'] + $result_complaints['compl_unreg_violation_car'] + $result_complaints['compl_unreg_violation_clpra'];


                  $reg_complaints_total_remarks = $result_complaints['compl_reg_remarks_fa'] + $result_complaints['compl_reg_remarks_pwa'] + $result_complaints['compl_reg_remarks_mba'] +
               $result_complaints['compl_reg_remarks_msihcr'] + $result_complaints['compl_reg_remarks_car'] + $result_complaints['compl_reg_remarks_clpra'];


                  $unreg_complaints_total_remarks = $result_complaints['compl_unreg_remarks_fa'] + $result_complaints['compl_unreg_remarks_pwa'] + $result_complaints['compl_unreg_remarks_mba'] +
               $result_complaints['compl_unreg_remarks_msihcr'] + $result_complaints['compl_unreg_remarks_car'] + $result_complaints['compl_unreg_remarks_clpra'];


          
    


  


       $query_update_tab8 = db_update('labour_factory_statcell_annual_report_t8');
       $query_update_tab8->fields(array(
       'reg_recv_no' =>$reg_complaints_total_no, 'reg_investigated' => $reg_complaints_total_inv, 'reg_violation' => $reg_complaints_total_vio, 'reg_action' => NULL, 'reg_remarks' => $reg_complaints_total_remarks, 'unreg_recv_no' => $unreg_complaints_total_inv, 'unreg_investigated' => $unreg_complaints_total_inv, 'unreg_violation' => $unreg_complaints_total_vio, 'unreg_action' => NULL, 'unreg_remarks' => $unreg_complaints_total_remarks ));
                    
                    
                    
       $query_update_tab8->condition('annual_inspection_id',$annualReportid);
     
       $query_update_tab8->execute(); 




          /*  end update complaints */



           /* update prosecution proceding  current year   */


                          db_delete('labour_factory_statcell_annual_report_t9_10')
                        ->condition('annual_inspection_id', $annualReportid)
                        ->execute();

                   $mr_prosecution_proceeding_instituted_select_query = db_select('labour_factory_statcell_form_5_t9_7_t6', 'a');
       
                         $mr_prosecution_proceeding_instituted_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.status','FS','=');

                          $mr_prosecution_proceeding_instituted_select_query->fields('a',array('form_type','pros_instituted_name_of_factory',
        'pros_instituted_address_of_factory','pros_instituted_reg_unreg','pros_instituted_person_prosecuted','pros_instituted_case_no','pros_instituted_name_of_act','pros_instituted_violation','pros_instituted_penal_provision','pros_instituted_name_of_court','pros_instituted_remarks_result'));

                   $mr_prosecution_proceeding_instituted_result = $mr_prosecution_proceeding_instituted_select_query->execute();

                     
                       if( $mr_prosecution_proceeding_instituted_result->rowCount() > 0 ) 
                       { 

                      foreach($mr_prosecution_proceeding_instituted_result as $squan) {

            $maxresult_t9=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t9_10'); 
          $result_t9=$maxresult_t9->fetchAssoc();
          $max_sl_number_t9 = trim($result_t9['maxsl']); 
        if($max_sl_number_t9==0){$querystring_t9=1; }else{ $querystring_t9=$max_sl_number_t9+1; }
        $row_id_t9=$querystring_t9;
    
            

  $fields_t9 = array('row_id' => $row_id_t9, 'annual_inspection_id' =>$annualReportid,'factory_name' =>trim($squan->pros_instituted_name_of_factory), 'factory_address' => trim($squan->pros_instituted_address_of_factory), 'reg_unreg' => trim($squan->pros_instituted_reg_unreg), 'person_prosecuted' => trim($squan->pros_instituted_person_prosecuted), 'case_number' => trim($squan->pros_instituted_case_no), 'court_name' => trim($squan->pros_instituted_name_of_court), 'violation_description' => trim($squan->pros_instituted_violation)
                         , 'results' =>  'PENDING', 'total_fine' => 0, 'is_pending' => 0);
      
       
                      db_insert('labour_factory_statcell_annual_report_t9_10')->fields($fields_t9)->execute();

                          
                      }
                  }
             


             /* update end prosecution proceding  current year */ 



              /*  update begin anr tab 11 */

           $no_pending_case_begin_year = db_select('labour_factory_statcell_annual_report_t11', 'a');
       
           $no_pending_case_begin_year->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
           $no_pending_case_begin_year->condition('b.inspector_id',trim($uid),'=');
           $no_pending_case_begin_year->condition('b.report_year',trim($thisYear),'=');

       

    $no_pending_case_begin_year->fields('a',array('case_pending_at_beginning','case_disposed_of_during',
        'case_pending_at_end'));

            $no_pending_case_begin_year_result = $no_pending_case_begin_year->execute();

             $result_pending_case_begin_year=$no_pending_case_begin_year_result->fetchAssoc();


                // 11. a


           $case_pending_at_end = !empty($result_pending_case_begin_year['case_pending_at_end']) ?  $result_pending_case_begin_year['case_pending_at_end'] : 0 ;


              

           $no_disposed_case_during_year = db_select('labour_factory_statcell_form_5_t10_7_t7', 'a');
       
           $no_disposed_case_during_year->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $no_disposed_case_during_year->condition('b.inspector_id',trim($uid),'=');
           $no_disposed_case_during_year->condition('a.case_disposed_date_of_disposal',trim($from),'>=');
           $no_disposed_case_during_year->condition('a.case_disposed_date_of_disposal',trim($to),'<=');
           $no_disposed_case_during_year->condition('b.status','FS','=');

           

           $no_disposed_case_during_year->addExpression('COALESCE(COUNT(case_disposed_name_of_factory),0)', 'no_disposed_case');
          

           

            $no_disposed_case_during_year_result = $no_disposed_case_during_year->execute();

             $result_disposed_case_year=$no_disposed_case_during_year_result->fetchAssoc();


             
              // 11 . b

               $no_disposed_case= $result_disposed_case_year['no_disposed_case'] ;

              // 11. c


              $no_of_case_pending_beganing_year=$case_pending_at_end - $no_disposed_case;


           





               // 13 ( seminar,training courses, etc conducted)

              
              $seminar_traning = db_select('labour_factory_statcell_form_5_t12_6_t5_7_t5', 'a');
       
           $seminar_traning->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $seminar_traning->condition('b.inspector_id',trim($uid),'=');
           $seminar_traning->condition('a.seminar_date_of_program',trim($from),'>=');
           $seminar_traning->condition('a.seminar_date_of_program',trim($to),'<=');
           $seminar_traning->condition('b.status','FS','=');

           
          $seminar_traning->fields('a',array('seminar_name_of_factory','seminar_address_of_factory',
             'seminar_type_of_program','seminar_date_of_program','seminar_no_of_participants','seminar_status_of_participants'));
         
          $seminar_traning_result = $seminar_traning->execute();

               $str_seminar=NULL;
                if( $seminar_traning_result->rowCount() > 0 ) 
                       { 
                   
                       $s=0;
                      foreach($seminar_traning_result as $squan) {
                        $s++;

                        $str_seminar.= $s .') Name of the Factory and Address : '.trim($squan->seminar_name_of_factory).' ,'.trim($squan->seminar_address_of_factory) .', Type of program:'.trim($squan->seminar_type_of_program) .', Date of program: '.trim($squan->seminar_date_of_program).', No of participants:'.trim($squan->seminar_no_of_participants).';'." ";
           

                   }



             
                 }

              // end no of seminar , trainging 



           


       $query_update_t11 = db_update('labour_factory_statcell_annual_report_t11');
       $query_update_t11->fields(array(
       'case_pending_at_beginning' =>$case_pending_at_end, 'case_disposed_of_during' => $no_disposed_case, 'case_pending_at_end' => $no_of_case_pending_beganing_year,  'seminar_training_courses' => $str_seminar ));
                    
                    
                    
       $query_update_t11->condition('annual_inspection_id',$annualReportid);
      
       $query_update_t11->execute(); 








                 /*  end update anr tab 11 */


        // begin tab 12 BOCW Act

           $tab_14_bocw = db_select('labour_factory_statcell_form_5_t14_6_t6_7_t8', 'a');
       
           $tab_14_bocw->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $tab_14_bocw->condition('b.inspector_id',trim($uid),'=');
           $tab_14_bocw->condition('b.report_from_date',trim($from),'>=');
           $tab_14_bocw->condition('b.report_to_date',trim($to),'<=');
           $tab_14_bocw->condition('b.status','FS','=');

           $tab_14_bocw->fields('a',array('no_of_units_visit ',
        'no_of_visit_paid_general' ,
    'no_of_visit_paid_complaint' ,
    'no_of_visit_paid_accident',
    'no_of_complaints_received' ,
    'details_of_complaint',
    'no_of_accidents_reported' ,
    'accident_details_name_of_deceased' ,
    'accident_details_age',
    'accident_details_sex' ,
    'accident_details_date_of_accident',
    'accident_details_nature_of_accident' ,
    'accident_details_description' ,
    'accident_details_place' ,
    'accident_details_name_of_employer' ,
    'accident_details_address_of_site' ,
    'details_of_violation_general_visit' ,
    'no_of_prosecution_general_visit',
    'no_of_prosecution_complaint',
    'no_of_prosecution_accident' ,
    'details_of_prosecution_violation' ,
    'details_of_prosecution_court_name',
    'details_of_prosecution_case_no' ,
    'details_of_prosecution_result' ,
    'other_information' ));
          

           

            $tab_14_bocw_result = $tab_14_bocw->execute();

             $result_tab14=$tab_14_bocw_result->fetchAssoc();


             
             

               $no_of_units_visit= !empty($result_tab14['no_of_units_visit']) ?  $result_tab14['no_of_units_visit'] : 0;
               $no_of_visit_paid_general= !empty($result_tab14['no_of_visit_paid_general']) ? $result_tab14['no_of_visit_paid_general'] : 0;
               $no_of_visit_paid_complaint= !empty($result_tab14['no_of_visit_paid_complaint'] ) ? $result_tab14['no_of_visit_paid_complaint'] : 0;
               $no_of_visit_paid_accident= !empty($result_tab14['no_of_visit_paid_accident']) ? $result_tab14['no_of_visit_paid_accident'] : 0;
               $no_of_complaints_received= !empty($result_tab14['no_of_complaints_received'] ) ? $result_tab14['no_of_complaints_received'] : 0;
               $details_of_complaint= $result_tab14['details_of_complaint'] ;
               $no_of_accidents_reported= !empty($result_tab14['no_of_accidents_reported']) ? $result_tab14['no_of_accidents_reported'] : 0;
               $accident_details_name_of_deceased= $result_tab14['accident_details_name_of_deceased'] ;
               $accident_details_age= !empty($result_tab14['accident_details_age']) ? $result_tab14['accident_details_age'] : 0;
               $accident_details_sex= $result_tab14['accident_details_sex'] ;
               $accident_details_date_of_accident= $result_tab14['accident_details_date_of_accident'] ;

                $accident_details_nature_of_accident= $result_tab14['accident_details_nature_of_accident'] ;
                $accident_details_description= $result_tab14['accident_details_description'] ;
                $accident_details_place= $result_tab14['accident_details_place'] ;
                $accident_details_name_of_employer= $result_tab14['accident_details_name_of_employer'] ;


                $accident_details_address_of_site= $result_tab14['accident_details_address_of_site'] ;
                $details_of_violation_general_visit= $result_tab14['details_of_violation_general_visit'] ;
                $no_of_prosecution_general_visit= !empty($result_tab14['no_of_prosecution_general_visit']) ? $result_tab14['no_of_prosecution_general_visit'] : 0;
                $no_of_prosecution_complaint= !empty($result_tab14['no_of_prosecution_complaint']) ? $result_tab14['no_of_prosecution_complaint'] : 0;


                $no_of_prosecution_accident= !empty($result_tab14['no_of_prosecution_accident']) ? $result_tab14['no_of_prosecution_accident'] : 0;
                $details_of_prosecution_violation= $result_tab14['details_of_prosecution_violation'] ;
                $details_of_prosecution_court_name= $result_tab14['details_of_prosecution_court_name'] ;
                $details_of_prosecution_case_no= $result_tab14['details_of_prosecution_case_no'] ;


                 $details_of_prosecution_result= $result_tab14['details_of_prosecution_result'] ;
                 $other_information= $result_tab14['other_information'] ;



             

            $visit_paid= $no_of_visit_paid_general + $no_of_visit_paid_complaint +  $no_of_visit_paid_accident;
            $no_prosecution= $no_of_prosecution_general_visit + $no_of_prosecution_complaint + $no_of_prosecution_accident ;


               
               
        $query_update_construct_t1 = db_update('labour_factory_statcell_annual_report_attach_construct_t1');
       $query_update_construct_t1->fields(array(
       'unit_visited' =>$no_of_units_visit, 'visit_paid' => $visit_paid,   'accident' => $no_of_accidents_reported, 'connection_accident' => $no_of_visit_paid_accident, 'complaints' => $no_of_complaints_received, 'connection_complaints' => $no_of_visit_paid_complaint, 'prosecution' => $no_prosecution ));
                    
                    
                    
       $query_update_construct_t1->condition('annual_inspection_id',$annualReportid);
     
       $query_update_construct_t1->execute(); 


      //Construction Works Case Details


           $cons_worker_case = db_select('labour_factory_statcell_form_5_t14_9', 'a');
           $cons_worker_case->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $cons_worker_case->condition('b.inspector_id',trim($uid),'=');
           $cons_worker_case->condition('b.report_from_date',trim($from),'>=');
           $cons_worker_case->condition('b.report_to_date',trim($to),'<=');
           $cons_worker_case->condition('b.status','FS','=');

            $cons_worker_case->fields('a',array('details_of_prosecution_violation','details_of_prosecution_court_name',
        'details_of_prosecution_case_no','details_of_prosecution_result'));

            $cons_worker_case_result = $cons_worker_case->execute();

                     
            if( $cons_worker_case_result->rowCount() > 0 ) 
                       { 

                      foreach($cons_worker_case_result as $squan) {

            $maxresult_cw_case=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_attach_construct_t2');  
          $result_cw_case=$maxresult_cw_case->fetchAssoc();
          $max_sl_number_cw_case = trim($result_cw_case['maxsl']); 
            if($max_sl_number_cw_case==0){$querystring_cw_case=1; }else{ $querystring_cw_case=$max_sl_number_cw_case+1; }
        $row_id_cw_case=$querystring_cw_case;
    


  $fields_cw_case = array('row_id' => $row_id_cw_case, 'annual_inspection_id' =>$annualReportid,'case_no' =>trim($squan->details_of_prosecution_case_no), 'violation' => trim($squan->details_of_prosecution_violation), 'court' => trim($squan->details_of_prosecution_court_name), 'remarks' => trim($squan->details_of_prosecution_result));
      
       
                      db_insert('labour_factory_statcell_annual_report_attach_construct_t2')->fields($fields_cw_case)->execute();

             }

         }

                   // end coonstractor case details


            
             // begin tab 12 maternity benefit



           
           

            $maternity_benefit = db_select('labour_factory_statcell_annual_report_attach_maternity_t1', 'a'); 
            $maternity_benefit->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
            $maternity_benefit->condition('b.inspector_id',trim($uid),'=');
            $maternity_benefit->condition('b.report_year',trim($thisYear),'=');
           

            $maternity_benefit->fields('a',array('case_pending_at_end_4_c'));

            $maternity_benefit_result = $maternity_benefit->execute();
            $result_maternity_benefit=$maternity_benefit_result->fetchAssoc();

           $case_pending_at_end_4_c=$result_maternity_benefit['case_pending_at_end_4_c'];


        



         $query_update_maternity_benefit = db_update('labour_factory_statcell_annual_report_attach_maternity_t1');
       $query_update_maternity_benefit->fields(array(
       'case_pending_at_beginning_4_a' => $case_pending_at_end_4_c ));
                    
                    
                    
       $query_update_maternity_benefit->condition('annual_inspection_id',$annualReportid);
     
       $query_update_maternity_benefit->execute();




                 
                       // end tab 12 maternity benefit



         // begin tab 12 Payment of wages



            $payment_wages = db_select('labour_factory_statcell_annual_report_attach_wages_t1', 'a'); 
            $payment_wages->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
            $payment_wages->condition('b.inspector_id',trim($uid),'=');
            $payment_wages->condition('b.report_year',trim($thisYear),'=');
           

            $payment_wages->fields('a',array('case_pending_at_end_3_c','app_pending_at_end_4_h'));

            $payment_wages_result = $payment_wages->execute();
            $result_payment_wages=$payment_wages_result->fetchAssoc();

        $case_pending_at_end_3_c=!empty($result_payment_wages['case_pending_at_end_3_c']) ? trim($result_payment_wages['case_pending_at_end_3_c']) : 0;
        $app_pending_at_end_4_h=!empty($result_payment_wages['app_pending_at_end_4_h']) ?  trim($result_payment_wages['app_pending_at_end_4_h']) : 0 ;




          
               
                   $mr_before_pw_act = db_select('labour_factory_statcell_form_5_t13', 'a');

                   $mr_before_pw_act->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                   $mr_before_pw_act->condition('b.inspector_id',trim($uid),'=');
                   $mr_before_pw_act->condition('b.report_from_date',trim($from),'>=');
                   $mr_before_pw_act->condition('b.report_to_date',trim($to),'<=');
                   $mr_before_pw_act->condition('b.status','FS','=');
                   $mr_before_pw_act->addExpression('COALESCE(count(pw_act_name_of_factory),0)', 'no_of_app');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_persons_involved), 0)', 'pw_act_persons_involved');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_amount_unpaid_wages),0)', 'pw_act_amount_unpaid_wages');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_amount_unauthorized_deduction),0)',
                  'pw_act_amount_unauthorized_deduction');

                  $mr_before_pw_act->addExpression("string_agg(pw_act_name_of_factory, ';')", "pw_act_name_of_factory");
                 

                  $mr_before_pw_act_result = $mr_before_pw_act->execute(); 
    
                  $result_before_pw_act=$mr_before_pw_act_result->fetchAssoc();

                  $pw_act_name_of_factory=$result_before_pw_act['pw_act_name_of_factory'];
                  $pw_act_persons_involved=$result_before_pw_act['pw_act_persons_involved'] ;
                  $pw_act_amount_unpaid_wages= $result_before_pw_act['pw_act_amount_unpaid_wages'] ;
                  $pw_act_amount_unauthorized_deduction=$result_before_pw_act['pw_act_amount_unauthorized_deduction'] ;

                  $no_of_app=$result_before_pw_act['no_of_app'] ; 
              


     $query_update_maternity_benefit = db_update('labour_factory_statcell_annual_report_attach_wages_t1');
       $query_update_maternity_benefit->fields(array(
       'case_pending_at_beginning_3_a' => $case_pending_at_end_3_c ,


'factories_name_4_a' => $pw_act_name_of_factory, 'application_filed_4_b' => $no_of_app, 'person_involved_4_c' => $pw_act_persons_involved, 'wages_claimed_4_d' => $pw_act_amount_unpaid_wages, 'deduction_claimed_4_e' => $pw_act_amount_unauthorized_deduction, 'app_pending_at_beginning_4_f' => $app_pending_at_end_4_h ));
                    
                    
                    
       $query_update_maternity_benefit->condition('annual_inspection_id',$annualReportid);
     
       $query_update_maternity_benefit->execute();



// end tab 12 payment of wages










           $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$annualReportid);
	           
	       drupal_goto($full_base);


           }

           }

           else
           {






            $maxresult=db_query('select  max(annual_inspection_id) maxsl from labour_factory_statcell_annual_report');	
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


                         $fieldsE = array('annual_inspection_id' => $autoGENNO, 'inspector_id' =>$uid,'area' =>$area, 'report_from_date' => $from, 'report_to_date' => $to, 'report_year' => $thisYear, 'annual_form_type' => $annual_report, 'status' => 'I', 'remarks' => NULL
                         , 'status_code' => NULL, 'last_updated' => date("Y-m-d"), 'is_submitted' => 0,  'is_processing' => 0 , 'is_accepted' => 0, 'accept_by' => 0, 'accept_date' => NULL, 'e_note' => NULL,'processed_data' => NULL ,'is_disabled' => 0,'create_by' => $uid,'create_date' => date("Y-m-d") ,'area_id' => $area_id);
		  
		   
                        db_insert('labour_factory_statcell_annual_report')->fields($fieldsE)->execute();



                          /* 1.   insert annual report a , b   */

             $step1_mr_select_query = db_select('labour_factory_statcell_form_5_6_7_t1', 'a');

           $step1_mr_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
          $step1_mr_select_query->condition('b.inspector_id',trim($uid),'=');
          $step1_mr_select_query->condition('b.report_from_date',trim($from),'>=');
          $step1_mr_select_query->condition('b.report_to_date',trim($to),'<=');
          $step1_mr_select_query->condition('b.status','FS','='); 


          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_2m_i),0)', 'g_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_2m_ii),0)', 'g_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_regfac_85),0)', 'g_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_2m_i),0)', 'g_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_2m_ii),0)', 'g_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_unregfac_85),0)', 'g_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_non_amendable),0)', 'g_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_nouv_total),0)', 'g_nouv_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_2m_i),0)', 'g_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_2m_ii),0)', 'g_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_regfac_85),0)', 'g_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_2m_i),0)', 'g_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_2m_ii),0)', 'g_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_unregfac_85),0)', 'g_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_non_amendable),0)', 'g_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(g_novp_total),0)', 'g_novp_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_2m_i),0)', 'h_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_2m_ii),0)', 'h_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_regfac_85),0)', 'h_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_2m_i),0)', 'h_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_2m_ii),0)', 'h_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_unregfac_85),0)', 'h_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_non_amendable),0)', 'h_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_nouv_total),0)', 'h_nouv_total');

          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_2m_i),0)', 'h_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_2m_ii),0)', 'h_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_regfac_85),0)', 'h_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_2m_i),0)', 'h_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_2m_ii),0)', 'h_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_unregfac_85),0)', 'h_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_non_amendable),0)', 'h_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(h_novp_total),0)', 'h_novp_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_2m_i),0)', 'mah_nouv_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_2m_ii),0)', 'mah_nouv_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_regfac_85),0)', 'mah_nouv_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_2m_i),0)', 'mah_nouv_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_2m_ii),0)', 'mah_nouv_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_unregfac_85),0)', 'mah_nouv_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_non_amendable),0)', 'mah_nouv_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_nouv_total),0)', 'mah_nouv_total');


          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_2m_i),0)', 'mah_novp_regfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_2m_ii),0)', 'mah_novp_regfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_regfac_85),0)', 'mah_novp_regfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_2m_i),0)', 'mah_novp_unregfac_2m_i');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_2m_ii),0)', 'mah_novp_unregfac_2m_ii');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_unregfac_85),0)', 'mah_novp_unregfac_85');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_non_amendable),0)', 'mah_novp_non_amendable');
          $step1_mr_select_query->addExpression('COALESCE(sum(mah_novp_total),0)', 'mah_novp_total');



		
       

         

        $step1_mr_select_query_result = $step1_mr_select_query->execute(); 


		
		$result_step1_A=$step1_mr_select_query_result->fetchAssoc();

		//print_r($result_step1_A);
         //exit;

		$g_nouv_regfac_2m_i=$result_step1_A['g_nouv_regfac_2m_i'];


		$g_nouv_regfac_2m_ii=$result_step1_A['g_nouv_regfac_2m_ii'];

		$g_nouv_regfac_85=$result_step1_A['g_nouv_regfac_85'];
		
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


    

     

      


            $maxresult_t1ab=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t1_a_b');	
	        $result_t1ab=$maxresult_t1ab->fetchAssoc();
	        $max_sl_number_t1ab = trim($result_t1ab['maxsl']); 
            if($max_sl_number_t1ab==0){$querystring_t1ab=1;	}else{ $querystring_t1ab=$max_sl_number_t1ab+1; }
		    $rowid_t1ab=$querystring_t1ab;

		   // print $rowid."--".$autoGENNO;
		  //  exit;



 $fieldsA = array('row_id' => $rowid_t1ab ,'annual_inspection_id' => $autoGENNO, 'g_nouv_regfac_2m_i' =>$g_nouv_regfac_2m_i,'g_nouv_regfac_2m_ii' =>$g_nouv_regfac_2m_ii, 'g_nouv_regfac_85' => $g_nouv_regfac_85, 'g_nouv_unregfac_2m_i' => $g_nouv_unregfac_2m_i, 'g_nouv_unregfac_2m_ii' => $g_nouv_unregfac_2m_ii, 'g_nouv_unregfac_85' => $g_nouv_unregfac_85, 'g_nouv_non_amendable' => $g_nouv_non_amendable, 'g_nouv_total' => $g_nouv_total,


    'g_novp_regfac_2m_i' => $g_novp_regfac_2m_i, 'g_novp_regfac_2m_ii' => $g_novp_regfac_2m_ii , 'g_novp_regfac_85' => $g_novp_regfac_85
 	, 'g_novp_unregfac_2m_i' => $g_novp_unregfac_2m_i , 'g_novp_unregfac_2m_ii' => $g_novp_unregfac_2m_ii , 'g_novp_unregfac_85' => $g_novp_unregfac_85 ,

 	'g_novp_non_amendable' => $g_novp_non_amendable , 'g_novp_total' => $g_novp_total,


   


 	'h_nouv_regfac_2m_i' => $h_nouv_regfac_2m_i, 'h_nouv_regfac_2m_ii' => $h_nouv_regfac_2m_ii , 'h_nouv_regfac_85' => $h_nouv_regfac_85
 	, 'h_nouv_unregfac_2m_i' => $h_nouv_unregfac_2m_i , 'h_nouv_unregfac_2m_ii' => $h_nouv_unregfac_2m_ii , 'h_nouv_unregfac_85' => $h_nouv_unregfac_85 ,

 	'h_nouv_non_amendable' => $h_nouv_non_amendable , 'h_nouv_total' => $h_nouv_total,



 	'h_novp_regfac_2m_i' => $h_novp_regfac_2m_i, 'h_novp_regfac_2m_ii' => $h_novp_regfac_2m_ii , 'h_novp_regfac_85' => $h_novp_regfac_85
 	, 'h_novp_unregfac_2m_i' => $h_novp_unregfac_2m_i , 'h_novp_unregfac_2m_ii' => $h_novp_unregfac_2m_ii , 'h_novp_unregfac_85' => $h_novp_unregfac_85 ,

 	'h_novp_non_amendable' => $h_novp_non_amendable , 'h_novp_total' => $h_novp_total,


 	'mah_nouv_regfac_2m_i' => $mah_nouv_regfac_2m_i, 'mah_nouv_regfac_2m_ii' => $mah_nouv_regfac_2m_ii , 'mah_nouv_regfac_85' => $mah_nouv_regfac_85
 	, 'mah_nouv_unregfac_2m_i' => $mah_nouv_unregfac_2m_i , 'mah_nouv_unregfac_2m_ii' => $mah_nouv_unregfac_2m_ii , 'mah_nouv_unregfac_85' => $mah_nouv_unregfac_85 ,

 	'mah_nouv_non_amendable' => $mah_nouv_non_amendable , 'mah_nouv_total' => $mah_nouv_total,


 	'mah_novp_regfac_2m_i' => $mah_novp_regfac_2m_i, 'mah_novp_regfac_2m_ii' => $mah_novp_regfac_2m_ii , 'mah_novp_regfac_85' => $mah_novp_regfac_85
 	, 'mah_novp_unregfac_2m_i' => $mah_novp_unregfac_2m_i , 'mah_novp_unregfac_2m_ii' => $mah_novp_unregfac_2m_ii , 'mah_novp_unregfac_85' => $mah_novp_unregfac_85 ,

 	'mah_novp_non_amendable' => $mah_novp_non_amendable , 'mah_novp_total' => $mah_novp_total,


    );
		  
db_insert('labour_factory_statcell_annual_report_t1_a_b')->fields($fieldsA)->execute();	


//exit;

                        



                          /*  1.  end No of units visited   */


                    /* 2.        No. of Special Visit                       */


                     $mr_specialVisit_select_query = db_select('labour_factory_statcell_form_5_6_7_t2', 'a');

                     $mr_specialVisit_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                     $mr_specialVisit_select_query->condition('b.inspector_id',trim($uid),'=');
                     $mr_specialVisit_select_query->condition('b.report_from_date',trim($from),'>=');
                     $mr_specialVisit_select_query->condition('b.report_to_date',trim($to),'<=');
                     $mr_specialVisit_select_query->condition('b.status','FS','=');
       
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_pwa),0)', 'visit_pwa');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_mba),0)', 'visit_mba');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_msihcr),0)', 'visit_msihcr');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_car),0)', 'visit_car');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_clpra),0)', 'visit_clpra');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_rest_interval),0)', 'visit_rest_interval');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_bef_after_legal_hours),0)', 'visit_bef_after_legal_hours');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_sunday_holiday),0)', 'visit_sunday_holiday');

                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_approval_of_plan),0)', 'visit_approval_of_plan');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_reg_licence),0)', 'visit_reg_licence');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_collection_statistics),0)', 'visit_collection_statistics');
                 $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_enq_complaints),0)', 'visit_enq_complaints');
                 $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_court_attendance),0)', 'visit_court_attendance');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_attn_seminar_meeting),0)', 'visit_attn_seminar_meeting');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_to_closed_factory),0)', 'visit_to_closed_factory');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_others),0)', 'visit_others');
                  $mr_specialVisit_select_query->addExpression('COALESCE(sum(visit_total),0)', 'visit_total');


               
                $mr_specialVisit_select_query_result = $mr_specialVisit_select_query->execute(); 
    
               $result_specialVisit=$mr_specialVisit_select_query_result->fetchAssoc();

               $visit_pwa=$result_specialVisit['visit_pwa'];
               $visit_mba=$result_specialVisit['visit_mba'];
               $visit_msihcr=$result_specialVisit['visit_msihcr'];
               $visit_car=$result_specialVisit['visit_car'];

               $visit_clpra=$result_specialVisit['visit_clpra'];
               $visit_rest_interval=$result_specialVisit['visit_rest_interval'];
               $visit_bef_after_legal_hours=$result_specialVisit['visit_bef_after_legal_hours'];
               $visit_sunday_holiday=$result_specialVisit['visit_sunday_holiday'];

               $visit_approval_of_plan=$result_specialVisit['visit_approval_of_plan'];
               $visit_reg_licence=$result_specialVisit['visit_reg_licence'];


               $visit_collection_statistics=$result_specialVisit['visit_collection_statistics'];
               $visit_enq_complaints=$result_specialVisit['visit_enq_complaints'];

               $visit_court_attendance=$result_specialVisit['visit_court_attendance'];
               $visit_attn_seminar_meeting=$result_specialVisit['visit_attn_seminar_meeting']; // not add annual report
               $visit_to_closed_factory=$result_specialVisit['visit_to_closed_factory'];
               $visit_others=$result_specialVisit['visit_others'];
               $visit_total=$result_specialVisit['visit_total'];







                $maxresult_t1d=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t1_d');	
	        $result_t1d=$maxresult_t1d->fetchAssoc();
	        $max_sl_number_t1d = trim($result_t1d['maxsl']); 
            if($max_sl_number_t1d==0){$querystring_t1d=1;	}else{ $querystring_t1d=$max_sl_number_t1d+1; }
		    $rowid_t1d=$querystring_t1d;

                  
                  $fieldsspecialVisit = array('row_id' => $rowid_t1d ,'annual_inspection_id' => $autoGENNO, 'visit_msihcr' =>$visit_msihcr,'visit_pwa' =>$visit_pwa, 'visit_mba' => $visit_mba, 'visit_car' => $visit_car, 'visit_clpra' => $visit_clpra, 'visit_rest_interval' => $visit_rest_interval, 'visit_bef_after_legal_hours' => $visit_bef_after_legal_hours, 'visit_sunday_holiday' => $visit_sunday_holiday,


    'visit_approval_of_plan' => $visit_approval_of_plan, 'visit_renew_licence' => $visit_reg_licence , 'visit_collection_statistics' => $visit_collection_statistics
 	, 'visit_enq_complaints' => $visit_enq_complaints , 'visit_court_prosecution' => $visit_court_attendance , 'visit_to_closed_factory' => $visit_to_closed_factory ,

 	'visit_others' => $visit_others , 'visit_total' => ($visit_total - $visit_attn_seminar_meeting),


         );
		  
      db_insert('labour_factory_statcell_annual_report_t1_d')->fields($fieldsspecialVisit)->execute(); 



                    /* 2. end no of  No. of Special Visit                              */



                    /* 3. accident and dangerous occurance     */

        $mr_ado_select_query = db_select('labour_factory_statcell_form_5_t3', 'a');
       
       $mr_ado_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
       $mr_ado_select_query->condition('b.inspector_id',trim($uid),'=');
       $mr_ado_select_query->condition('b.report_from_date',trim($from),'>=');
       $mr_ado_select_query->condition('b.report_to_date',trim($to),'<=');
       $mr_ado_select_query->condition('b.status','FS','=');

        $mr_ado_select_query->addExpression('COALESCE(sum(no_fatal),0)', 'no_fatal');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_serious),0)', 'no_serious');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_explosion),0)', 'no_explosion');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_fire),0)', 'no_fire');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_gassing),0)', 'no_gassing');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_toxic_release),0)', 'no_toxic_release');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_collapse),0)', 'no_collapse');
        $mr_ado_select_query->addExpression('COALESCE(sum(no_others),0)', 'no_others');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_fatal),0)', 'visit_fatal');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_serious),0)', 'visit_serious');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_explosion),0)', 'visit_explosion');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_fire),0)', 'visit_fire');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_gassing),0)', 'visit_gassing');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_toxic_release),0)', 'visit_toxic_release');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_collapse),0)', 'visit_collapse');
        $mr_ado_select_query->addExpression('COALESCE(sum(visit_others),0)', 'visit_others');

     
      
		
       
        $mr_ado_select_query_result = $mr_ado_select_query->execute(); 
		
		$result_mrado=$mr_ado_select_query_result->fetchAssoc();
		$ado_no_of_accidents_fatal=$result_mrado['no_fatal'];
        $ado_no_of_accidents_serious=$result_mrado['no_serious'];
        $no_fire=$result_mrado['no_fire'];
        $no_explosion=$result_mrado['no_explosion'];
        $ado_no_danger_occur_gassing=$result_mrado['no_gassing'];
		
		$ado_no_danger_occur_toxic_release=$result_mrado['no_toxic_release'];
		$ado_no_danger_occur_collapse=$result_mrado['no_collapse'];

		$ado_no_danger_occur_others=$result_mrado['no_others'];


	   $ado_no_visit_paid_fatal_accidents=$result_mrado['visit_fatal'];
       $visit_serious=$result_mrado['visit_serious'];
	   $visit_explosion=$result_mrado['visit_explosion'];
	   $visit_fire=$result_mrado['visit_fire'];
	   $ado_no_visit_paid_gassing=$result_mrado['visit_gassing'];
	   $ado_no_visit_paid_toxic_release=$result_mrado['visit_toxic_release'];
	   $ado_no_visit_paid_collapse=$result_mrado['visit_collapse'];
	   $ado_no_visit_paid_others=$result_mrado['visit_others'];


	        $maxresult_t2a=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t2_a');	
	        $result_t2a=$maxresult_t2a->fetchAssoc();
	        $max_sl_number_t2a = trim($result_t2a['maxsl']); 
            if($max_sl_number_t2a==0){$querystring_t2a=1;	}else{ $querystring_t2a=$max_sl_number_t2a+1; }
		    $rowid_t2a=$querystring_t2a;



                  $fieldsAdoMr = array('row_id' => $rowid_t2a, 'annual_inspection_id' =>$autoGENNO,'ado_no_of_accidents_fatal' =>$ado_no_of_accidents_fatal, 'ado_no_of_accidents_serious' => $ado_no_of_accidents_serious, 'ado_no_danger_occur_explosion' => $no_explosion, 'ado_no_danger_occur_fire' => $no_fire, 'ado_no_danger_occur_gassing' => $ado_no_danger_occur_gassing, 'ado_no_danger_occur_toxic_release' => $ado_no_danger_occur_toxic_release, 'ado_no_danger_occur_collapse' => $ado_no_danger_occur_collapse, 'ado_no_danger_occur_others' => $ado_no_danger_occur_others, 'ado_no_visit_paid_fatal_accidents' => $ado_no_visit_paid_fatal_accidents, 'ado_no_visit_paid_serious_accidents' => $visit_serious, 'ado_no_visit_paid_explosion' => $visit_explosion, 'ado_no_visit_paid_fire' => $visit_fire, 'ado_no_visit_paid_gassing' => $ado_no_visit_paid_gassing,'ado_no_visit_paid_toxic_release' => $ado_no_visit_paid_toxic_release,'ado_no_visit_paid_collapse' => $ado_no_visit_paid_collapse,'ado_no_visit_paid_others' => $ado_no_visit_paid_others);
		  
		   
                     db_insert('labour_factory_statcell_annual_report_t2_a')->fields($fieldsAdoMr)->execute();

                  
                    /* end accident and dangerous    */

                    /*  begin details of fatal & serious accident  */

                          $mr_det_fatal_serious_select_query = db_select('labour_factory_statcell_form_5_t4a', 'a');
       
                         $mr_det_fatal_serious_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_det_fatal_serious_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_det_fatal_serious_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_det_fatal_serious_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_det_fatal_serious_select_query->condition('b.status','FS','=');

                          $mr_det_fatal_serious_select_query->fields('a',array('acc_det_name_of_factory','acc_det_address_of_factory',
        'acc_det_name_of_deceased_injured','acc_det_date_of_accident','classification_code'));

                         $mr_det_fatal_serious_select_query_result = $mr_det_fatal_serious_select_query->execute();

                     
                       if($mr_det_fatal_serious_select_query_result->rowCount() > 0) 
                       { 

                      foreach($mr_det_fatal_serious_select_query_result as $squan) {
                      


                


              $maxresult_t2b=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t2_b');	
	        $result_t2b=$maxresult_t2b->fetchAssoc();
	        $max_sl_number_t2b = trim($result_t2b['maxsl']); 
            if($max_sl_number_t2b==0){$querystring_t2b=1;	}else{ $querystring_t2b=$max_sl_number_t2b+1; }
		      $rowid_t2b=$querystring_t2b;
           

                $fieldsE_t2_b = array('row_id' => $rowid_t2b, 'annual_inspection_id' => $autoGENNO,'accident_type' =>'Serious' ,'acc_det_name_of_factory' =>trim($squan->acc_det_name_of_factory),'acc_det_address_of_factory' =>trim($squan->acc_det_address_of_factory), 'acc_det_name_of_deceased_injured' => trim($squan->acc_det_name_of_deceased_injured), 'acc_det_date_of_accident' => $squan->acc_det_date_of_accident,   'classification_code' => $squan->classification_code );
		  
		   
          db_insert('labour_factory_statcell_annual_report_t2_b')->fields($fieldsE_t2_b)->execute();	
		   
          

       }
   }
               

                    /* end details of fatal & serious accident*/




                    /*  start orders issued under various act & rules */

                      
                          $mr_order_issue_act_rule_select_query = db_select('labour_factory_statcell_form_5_t7', 'a');
       
                         $mr_order_issue_act_rule_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_order_issue_act_rule_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_order_issue_act_rule_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_order_issue_act_rule_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_order_issue_act_rule_select_query->condition('b.status','FS','=');

                          $mr_order_issue_act_rule_select_query->fields('a',array('factory_name','factory_address',
        'acts_issued','time_allowed','result_description'));

                         $mr_order_issue_act_rule_select_query_result = $mr_order_issue_act_rule_select_query->execute();

                     
                       if($mr_order_issue_act_rule_select_query_result->rowCount() > 0) 
                       { 

                      foreach($mr_order_issue_act_rule_select_query_result as $squan) {

                         

                       

                           $maxresult_t4=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t4');	
	                       $result_t4=$maxresult_t4->fetchAssoc();
	                       $max_sl_number_t4 = trim($result_t4['maxsl']); 
                         if($max_sl_number_t4==0){$querystring_t4=1;	}else{ $querystring_t4=$max_sl_number_t4+1; }
		                  $rowid_t4=$querystring_t4;


		
	      
		   
		    $fieldsE_t4 = array('row_id' => $rowid_t4, 'annual_inspection_id' => $autoGENNO,'factory_name' =>trim($squan->factory_name) ,'factory_address' =>trim($squan->factory_address),'section_rule_issued' =>trim($squan->acts_issued), 'time_allowed' => trim($squan->time_allowed), 'brief_description' => trim($squan->result_description));
		  
		   
           db_insert('labour_factory_statcell_annual_report_t4')->fields($fieldsE_t4)->execute();




                      }
                  }




                    /*  end  orders issued under various act & rules */



                    /* start complaints */

                   $mr_complaints_select_query = db_select('labour_factory_statcell_form_5_t8', 'a');

                   $mr_complaints_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                   $mr_complaints_select_query->condition('b.inspector_id',trim($uid),'=');
                   $mr_complaints_select_query->condition('b.report_from_date',trim($from),'>=');
                   $mr_complaints_select_query->condition('b.report_to_date',trim($to),'<=');
                   $mr_complaints_select_query->condition('b.status','FS','=');
       
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_fa),0)', 'compl_reg_no_rec_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_pwa),0)', 'compl_reg_no_rec_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_mba),0)', 'compl_reg_no_rec_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_msihcr),0)', 'compl_reg_no_rec_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_car),0)', 'compl_reg_no_rec_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_rec_clpra),0)', 'compl_reg_no_rec_clpra');

                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_fa),0)', 'compl_unreg_no_rec_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_pwa),0)', 'compl_unreg_no_rec_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_mba),0)', 'compl_unreg_no_rec_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_msihcr),0)', 'compl_unreg_no_rec_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_car),0)', 'compl_unreg_no_rec_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_rec_clpra),0)', 'compl_unreg_no_rec_clpra');


                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_fa),0)', 'compl_reg_no_inv_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_pwa),0)', 'compl_reg_no_inv_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_mba),0)', 'compl_reg_no_inv_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_msihcr),0)', 'compl_reg_no_inv_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_car),0)', 'compl_reg_no_inv_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_reg_no_inv_clpra),0)', 'compl_reg_no_inv_clpra');

                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_fa),0)', 'compl_unreg_no_inv_fa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_pwa),0)', 'compl_unreg_no_inv_pwa');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_mba),0)', 'compl_unreg_no_inv_mba');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_msihcr),0)', 'compl_unreg_no_inv_msihcr');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_car),0)', 'compl_unreg_no_inv_car');
                  $mr_complaints_select_query->addExpression('COALESCE(sum(compl_unreg_no_inv_clpra),0)', 'compl_unreg_no_inv_clpra');


                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_fa, ';')", "compl_reg_violation_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_pwa, ';')", "compl_reg_violation_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_mba, ';')", "compl_reg_violation_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_msihcr, ';')", "compl_reg_violation_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_car, ';')", "compl_reg_violation_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_violation_clpra, ';')", "compl_reg_violation_clpra");

                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_fa, ';')", "compl_unreg_violation_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_pwa, ';')", "compl_unreg_violation_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_mba, ';')", "compl_unreg_violation_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_msihcr, ';')", "compl_unreg_violation_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_car, ';')", "compl_unreg_violation_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_violation_clpra, ';')", "compl_unreg_violation_clpra");


                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_fa, ';')", "compl_reg_remarks_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_pwa, ';')", "compl_reg_remarks_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_mba, ';')", "compl_reg_remarks_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_msihcr, ';')", "compl_reg_remarks_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_car, ';')", "compl_reg_remarks_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_reg_remarks_clpra, ';')", "compl_reg_remarks_clpra");

                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_fa, ';')", "compl_unreg_remarks_fa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_pwa, ';')", "compl_unreg_remarks_pwa");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_mba, ';')", "compl_unreg_remarks_mba");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_msihcr, ';')", "compl_unreg_remarks_msihcr");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_car, ';')", "compl_unreg_remarks_car");
                  $mr_complaints_select_query->addExpression("string_agg(compl_unreg_remarks_clpra, ';')", "compl_unreg_remarks_clpra");
        



               
                $mr_complaints_select_query_result = $mr_complaints_select_query->execute(); 
    
                $result_complaints=$mr_complaints_select_query_result->fetchAssoc();



               $reg_complaints_total_no = $result_complaints['compl_reg_no_rec_fa'] + $result_complaints['compl_reg_no_rec_pwa'] + $result_complaints['compl_reg_no_rec_mba'] + $result_complaints['compl_reg_no_rec_msihcr'] + $result_complaints['compl_reg_no_rec_car'] + $result_complaints['compl_reg_no_rec_clpra'];

               $unreg_complaints_total_no = $result_complaints['compl_unreg_no_rec_fa'] + $result_complaints['compl_unreg_no_rec_pwa'] + $result_complaints['compl_unreg_no_rec_mba'] + $result_complaints['compl_unreg_no_rec_msihcr'] + $result_complaints['compl_unreg_no_rec_car'] + $result_complaints['compl_unreg_no_rec_clpra'];

               $reg_complaints_total_inv = $result_complaints['compl_reg_no_inv_fa'] + $result_complaints['compl_reg_no_inv_pwa'] + $result_complaints['compl_reg_no_inv_mba'] + $result_complaints['compl_reg_no_inv_msihcr'] + $result_complaints['compl_reg_no_inv_car'] + $result_complaints['compl_reg_no_inv_clpra'];

               $unreg_complaints_total_inv = $result_complaints['compl_unreg_no_inv_fa'] + $result_complaints['compl_unreg_no_inv_pwa'] + $result_complaints['compl_unreg_no_inv_mba'] + $result_complaints['compl_unreg_no_inv_msihcr'] + $result_complaints['compl_unreg_no_inv_car'] + $result_complaints['compl_unreg_no_inv_clpra'];

               $reg_complaints_total_vio = $result_complaints['compl_reg_violation_fa'] + $result_complaints['compl_reg_violation_pwa'] + $result_complaints['compl_reg_violation_mba'] +
               $result_complaints['compl_reg_violation_msihcr'] + $result_complaints['compl_reg_violation_car'] + $result_complaints['compl_reg_violation_clpra'];

               $unreg_complaints_total_vio = $result_complaints['compl_unreg_violation_fa'] + $result_complaints['compl_unreg_violation_pwa'] + $result_complaints['compl_unreg_violation_mba'] +
                 + $result_complaints['compl_unreg_violation_msihcr'] + $result_complaints['compl_unreg_violation_car'] + $result_complaints['compl_unreg_violation_clpra'];


                  $reg_complaints_total_remarks = $result_complaints['compl_reg_remarks_fa'] + $result_complaints['compl_reg_remarks_pwa'] + $result_complaints['compl_reg_remarks_mba'] +
               $result_complaints['compl_reg_remarks_msihcr'] + $result_complaints['compl_reg_remarks_car'] + $result_complaints['compl_reg_remarks_clpra'];


                  $unreg_complaints_total_remarks = $result_complaints['compl_unreg_remarks_fa'] + $result_complaints['compl_unreg_remarks_pwa'] + $result_complaints['compl_unreg_remarks_mba'] +
               $result_complaints['compl_unreg_remarks_msihcr'] + $result_complaints['compl_unreg_remarks_car'] + $result_complaints['compl_unreg_remarks_clpra'];


            $maxresult_t8=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t8');	
	        $result_t8=$maxresult_t8->fetchAssoc();
	        $max_sl_number_t8 = trim($result_t8['maxsl']); 
            if($max_sl_number_t8==0){$querystring_t8=1;	}else{ $querystring_t8=$max_sl_number_t8+1; }
		    $row_id_t8=$querystring_t8;
    


  $fieldsE_t8 = array('row_id' => $row_id_t8, 'annual_inspection_id' =>$autoGENNO,'reg_recv_no' =>$reg_complaints_total_no, 'reg_investigated' => $reg_complaints_total_inv, 'reg_violation' => $reg_complaints_total_vio, 'reg_action' => NULL, 'reg_remarks' => $reg_complaints_total_remarks, 'unreg_recv_no' => $unreg_complaints_total_inv, 'unreg_investigated' => $unreg_complaints_total_inv, 'unreg_violation' => $unreg_complaints_total_vio, 'unreg_action' => NULL, 'unreg_remarks' => $unreg_complaints_total_remarks);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t8')->fields($fieldsE_t8)->execute();


          /*  end complaints */

           /* prosecution proceding  current year   */

                   $mr_prosecution_proceeding_instituted_select_query = db_select('labour_factory_statcell_form_5_t9_7_t6', 'a');
       
                         $mr_prosecution_proceeding_instituted_select_query->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.inspector_id',trim($uid),'=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.report_from_date',trim($from),'>=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.report_to_date',trim($to),'<=');
                         $mr_prosecution_proceeding_instituted_select_query->condition('b.status','FS','=');

                          $mr_prosecution_proceeding_instituted_select_query->fields('a',array('form_type','pros_instituted_name_of_factory',
        'pros_instituted_address_of_factory','pros_instituted_reg_unreg','pros_instituted_person_prosecuted','pros_instituted_case_no','pros_instituted_name_of_act','pros_instituted_violation','pros_instituted_penal_provision','pros_instituted_name_of_court','pros_instituted_remarks_result'));

                   $mr_prosecution_proceeding_instituted_result = $mr_prosecution_proceeding_instituted_select_query->execute();

                     
                       if( $mr_prosecution_proceeding_instituted_result->rowCount() > 0 ) 
                       { 

                      foreach($mr_prosecution_proceeding_instituted_result as $squan) {

            $maxresult_t9=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t9_10');	
	        $result_t9=$maxresult_t9->fetchAssoc();
	        $max_sl_number_t9 = trim($result_t9['maxsl']); 
            if($max_sl_number_t9==0){$querystring_t9=1;	}else{ $querystring_t9=$max_sl_number_t9+1; }
		    $row_id_t9=$querystring_t9;
    
            

  $fields_t9 = array('row_id' => $row_id_t9, 'annual_inspection_id' =>$autoGENNO,'factory_name' =>trim($squan->pros_instituted_name_of_factory), 'factory_address' => trim($squan->pros_instituted_address_of_factory), 'reg_unreg' => trim($squan->pros_instituted_reg_unreg), 'person_prosecuted' => trim($squan->pros_instituted_person_prosecuted), 'case_number' => trim($squan->pros_instituted_case_no), 'court_name' => trim($squan->pros_instituted_name_of_court), 'violation_description' => trim($squan->pros_instituted_violation)
                         , 'results' =>  'PENDING', 'total_fine' => 0, 'is_pending' => 0);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t9_10')->fields($fields_t9)->execute();

                          
                      }
                  }
             


             /* end prosecution proceding  current year */ 

             //print $previous_from_year_dt."==".$previous_to_year_dt;
             //exit;

             /* begin pending cases previous years    */

         /*  $mr_pending_case_select_query = db_select('labour_factory_statcell_annual_report_t9_10', 'a');
       
           $mr_pending_case_select_query->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
           $mr_pending_case_select_query->condition('b.inspector_id',trim($uid),'=');
           $mr_pending_case_select_query->condition('b.report_from_date',trim($previous_from_year_dt),'>=');
           $mr_pending_case_select_query->condition('b.report_to_date',trim($previous_to_year_dt),'<=');
           $mr_pending_case_select_query->condition('a.results','PENDING','=');

            $mr_pending_case_select_query->fields('a',array('factory_name','factory_address',
        'reg_unreg','person_prosecuted','case_number','court_name','violation_description','results','total_fine'));

            $mr_pending_case_select_query_result = $mr_pending_case_select_query->execute();

                     
            if( $mr_pending_case_select_query_result->rowCount() > 0 ) 
                       { 

                      foreach($mr_pending_case_select_query_result as $squan) {

            $maxresult_t10=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t9_10');	
	        $result_t10=$maxresult_t10->fetchAssoc();
	        $max_sl_number_t10 = trim($result_t10['maxsl']); 
            if($max_sl_number_t10==0){$querystring_t10=1;	}else{ $querystring_t10=$max_sl_number_t10+1; }
		    $row_id_t10=$querystring_t10;
    


  $fields_t10 = array('row_id' => $row_id_t10, 'annual_inspection_id' =>$autoGENNO,'factory_name' =>trim($squan->factory_name), 'factory_address' => trim($squan->factory_address), 'reg_unreg' => trim($squan->reg_unreg), 'person_prosecuted' => trim($squan->person_prosecuted), 'case_number' => trim($squan->case_number), 'court_name' => trim($squan->court_name), 'violation_description' => trim($squan->violation_description)
                         , 'results' => trim($squan->results), 'total_fine' => trim($squan->total_fine));
		  
		   
                    // db_insert('labour_factory_statcell_annual_report_t9_10')->fields($fields_t10)->execute();



                      }

                  } */

                 /* end pending cases previous years   */


                 /*  begin anr tab 11 */

           $no_pending_case_begin_year = db_select('labour_factory_statcell_annual_report_t11', 'a');
       
           $no_pending_case_begin_year->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
           $no_pending_case_begin_year->condition('b.inspector_id',trim($uid),'=');
           $no_pending_case_begin_year->condition('b.report_year',trim($thisYear),'=');

       

    $no_pending_case_begin_year->fields('a',array('case_pending_at_beginning','case_disposed_of_during',
        'case_pending_at_end'));

            $no_pending_case_begin_year_result = $no_pending_case_begin_year->execute();

             $result_pending_case_begin_year=$no_pending_case_begin_year_result->fetchAssoc();


                // 11. a


           $case_pending_at_end = !empty($result_pending_case_begin_year['case_pending_at_end']) ?  $result_pending_case_begin_year['case_pending_at_end'] : 0 ;


              

              


           


            $no_disposed_case_during_year = db_select('labour_factory_statcell_form_5_t10_7_t7', 'a');
       
           $no_disposed_case_during_year->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $no_disposed_case_during_year->condition('b.inspector_id',trim($uid),'=');
           $no_disposed_case_during_year->condition('a.case_disposed_date_of_disposal',trim($from),'>=');
           $no_disposed_case_during_year->condition('a.case_disposed_date_of_disposal',trim($to),'<=');
           $no_disposed_case_during_year->condition('b.status','FS','=');

           

           $no_disposed_case_during_year->addExpression('COALESCE(COUNT(case_disposed_name_of_factory),0)', 'no_disposed_case');
          

           

            $no_disposed_case_during_year_result = $no_disposed_case_during_year->execute();

             $result_disposed_case_year=$no_disposed_case_during_year_result->fetchAssoc();


             
              // 11 . b

               $no_disposed_case= $result_disposed_case_year['no_disposed_case'] ;

              // 11. c


              $no_of_case_pending_beganing_year=$case_pending_at_end - $no_disposed_case;


           





               // 13 ( seminar,training courses, etc conducted)

              
              $seminar_traning = db_select('labour_factory_statcell_form_5_t12_6_t5_7_t5', 'a');
       
           $seminar_traning->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $seminar_traning->condition('b.inspector_id',trim($uid),'=');
           $seminar_traning->condition('a.seminar_date_of_program',trim($from),'>=');
           $seminar_traning->condition('a.seminar_date_of_program',trim($to),'<=');
           $seminar_traning->condition('b.status','FS','=');

           
          $seminar_traning->fields('a',array('seminar_name_of_factory','seminar_address_of_factory',
             'seminar_type_of_program','seminar_date_of_program','seminar_no_of_participants','seminar_status_of_participants'));
         
          $seminar_traning_result = $seminar_traning->execute();

               $str_seminar=NULL;
                if( $seminar_traning_result->rowCount() > 0 ) 
                       { 
                   
                       $s=0;
                      foreach($seminar_traning_result as $squan) {
                      	$s++;

                      	$str_seminar.= $s .') Name of the Factory and Address : '.trim($squan->seminar_name_of_factory).' ,'.trim($squan->seminar_address_of_factory) .', Type of program:'.trim($squan->seminar_type_of_program) .', Date of program: '.trim($squan->seminar_date_of_program).', No of participants:'.trim($squan->seminar_no_of_participants).';'." ";
           

                   }



             
                 }

              // end no of seminar , trainging 
               




                       
            $maxresult_t11=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t11');	
	        $result_11=$maxresult_t11->fetchAssoc();
	        $max_sl_number_11 = trim($result_11['maxsl']); 
            if($max_sl_number_11==0){$querystring_11=1;	}else{ $querystring_11=$max_sl_number_11+1; }
		    $row_id_t11=$querystring_11;

 $fields_t11 = array('row_id' => $row_id_t11, 'annual_inspection_id' =>$autoGENNO,'case_pending_at_beginning' =>$case_pending_at_end, 'case_disposed_of_during' => $no_disposed_case, 'case_pending_at_end' => $no_of_case_pending_beganing_year,  'seminar_training_courses' => $str_seminar);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t11')->fields($fields_t11)->execute();



                 /*  end anr tab 11 */

               

                      // begin tab 12 BOCW Act

           $tab_14_bocw = db_select('labour_factory_statcell_form_5_t14_6_t6_7_t8', 'a');
       
           $tab_14_bocw->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $tab_14_bocw->condition('b.inspector_id',trim($uid),'=');
           $tab_14_bocw->condition('b.report_from_date',trim($from),'>=');
           $tab_14_bocw->condition('b.report_to_date',trim($to),'<=');
           $tab_14_bocw->condition('b.status','FS','=');

           $tab_14_bocw->fields('a',array('no_of_units_visit ',
        'no_of_visit_paid_general' ,
    'no_of_visit_paid_complaint' ,
    'no_of_visit_paid_accident',
    'no_of_complaints_received' ,
    'details_of_complaint',
    'no_of_accidents_reported' ,
    'accident_details_name_of_deceased' ,
    'accident_details_age',
    'accident_details_sex' ,
    'accident_details_date_of_accident',
    'accident_details_nature_of_accident' ,
    'accident_details_description' ,
    'accident_details_place' ,
    'accident_details_name_of_employer' ,
    'accident_details_address_of_site' ,
    'details_of_violation_general_visit' ,
    'no_of_prosecution_general_visit',
    'no_of_prosecution_complaint',
    'no_of_prosecution_accident' ,
    'details_of_prosecution_violation' ,
    'details_of_prosecution_court_name',
    'details_of_prosecution_case_no' ,
    'details_of_prosecution_result' ,
    'other_information' ));
          

           

            $tab_14_bocw_result = $tab_14_bocw->execute();

             $result_tab14=$tab_14_bocw_result->fetchAssoc();


             
             

               $no_of_units_visit= !empty($result_tab14['no_of_units_visit']) ?  $result_tab14['no_of_units_visit'] : 0;
               $no_of_visit_paid_general= !empty($result_tab14['no_of_visit_paid_general']) ? $result_tab14['no_of_visit_paid_general'] : 0;
               $no_of_visit_paid_complaint= !empty($result_tab14['no_of_visit_paid_complaint'] ) ? $result_tab14['no_of_visit_paid_complaint'] : 0;
               $no_of_visit_paid_accident= !empty($result_tab14['no_of_visit_paid_accident']) ? $result_tab14['no_of_visit_paid_accident'] : 0;
               $no_of_complaints_received= !empty($result_tab14['no_of_complaints_received'] ) ? $result_tab14['no_of_complaints_received'] : 0;
               $details_of_complaint= $result_tab14['details_of_complaint'] ;
               $no_of_accidents_reported= !empty($result_tab14['no_of_accidents_reported']) ? $result_tab14['no_of_accidents_reported'] : 0;
               $accident_details_name_of_deceased= $result_tab14['accident_details_name_of_deceased'] ;
               $accident_details_age= !empty($result_tab14['accident_details_age']) ? $result_tab14['accident_details_age'] : 0;
               $accident_details_sex= $result_tab14['accident_details_sex'] ;
               $accident_details_date_of_accident= $result_tab14['accident_details_date_of_accident'] ;

                $accident_details_nature_of_accident= $result_tab14['accident_details_nature_of_accident'] ;
                $accident_details_description= $result_tab14['accident_details_description'] ;
                $accident_details_place= $result_tab14['accident_details_place'] ;
                $accident_details_name_of_employer= $result_tab14['accident_details_name_of_employer'] ;


                $accident_details_address_of_site= $result_tab14['accident_details_address_of_site'] ;
                $details_of_violation_general_visit= $result_tab14['details_of_violation_general_visit'] ;
                $no_of_prosecution_general_visit= !empty($result_tab14['no_of_prosecution_general_visit']) ? $result_tab14['no_of_prosecution_general_visit'] : 0;
                $no_of_prosecution_complaint= !empty($result_tab14['no_of_prosecution_complaint']) ? $result_tab14['no_of_prosecution_complaint'] : 0;


                $no_of_prosecution_accident= !empty($result_tab14['no_of_prosecution_accident']) ? $result_tab14['no_of_prosecution_accident'] : 0;
                $details_of_prosecution_violation= $result_tab14['details_of_prosecution_violation'] ;
                $details_of_prosecution_court_name= $result_tab14['details_of_prosecution_court_name'] ;
                $details_of_prosecution_case_no= $result_tab14['details_of_prosecution_case_no'] ;


                 $details_of_prosecution_result= $result_tab14['details_of_prosecution_result'] ;
                 $other_information= $result_tab14['other_information'] ;



             $maxresult_t12_a=db_query('select  max(construction_row_id) maxsl from labour_factory_statcell_annual_report_attach_construct_t1');	
	        $result_12_a=$maxresult_t12_a->fetchAssoc();
	        $max_sl_number_12_a = trim($result_12_a['maxsl']); 
            if($max_sl_number_12_a==0){$querystring_12_a=1;	}else{ $querystring_12_a=$max_sl_number_12_a+1; }
		    $construction_row_id_12_a=$querystring_12_a;

            $visit_paid= $no_of_visit_paid_general + $no_of_visit_paid_complaint +  $no_of_visit_paid_accident;
            $no_prosecution= $no_of_prosecution_general_visit + $no_of_prosecution_complaint + $no_of_prosecution_accident ;


               
               
              

 $fieldsE_t12_a = array('construction_row_id' => $construction_row_id_12_a, 'annual_inspection_id' =>$autoGENNO,'unit_visited' =>$no_of_units_visit, 'visit_paid' => $visit_paid,   'accident' => $no_of_accidents_reported, 'connection_accident' => $no_of_visit_paid_accident, 'complaints' => $no_of_complaints_received, 'connection_complaints' => $no_of_visit_paid_complaint, 'prosecution' => $no_prosecution);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_construct_t1')->fields($fieldsE_t12_a)->execute();

                   


                 //Construction Works Case Details


           $cons_worker_case = db_select('labour_factory_statcell_form_5_t14_9', 'a');
           $cons_worker_case->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
           $cons_worker_case->condition('b.inspector_id',trim($uid),'=');
           $cons_worker_case->condition('b.report_from_date',trim($from),'>=');
           $cons_worker_case->condition('b.report_to_date',trim($to),'<=');
           $cons_worker_case->condition('b.status','FS','=');

            $cons_worker_case->fields('a',array('details_of_prosecution_violation','details_of_prosecution_court_name',
        'details_of_prosecution_case_no','details_of_prosecution_result'));

            $cons_worker_case_result = $cons_worker_case->execute();

                     
            if( $cons_worker_case_result->rowCount() > 0 ) 
                       { 

                      foreach($cons_worker_case_result as $squan) {

            $maxresult_cw_case=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_attach_construct_t2');	
	        $result_cw_case=$maxresult_cw_case->fetchAssoc();
	        $max_sl_number_cw_case = trim($result_cw_case['maxsl']); 
            if($max_sl_number_cw_case==0){$querystring_cw_case=1;	}else{ $querystring_cw_case=$max_sl_number_cw_case+1; }
		    $row_id_cw_case=$querystring_cw_case;
    


  $fields_cw_case = array('row_id' => $row_id_cw_case, 'annual_inspection_id' =>$autoGENNO,'case_no' =>trim($squan->details_of_prosecution_case_no), 'violation' => trim($squan->details_of_prosecution_violation), 'court' => trim($squan->details_of_prosecution_court_name), 'remarks' => trim($squan->details_of_prosecution_result));
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_construct_t2')->fields($fields_cw_case)->execute();

             }

         }

                   // end coonstractor case details   




                     // end tab 12 BOCW act


                       // begin tab 12 maternity benefit



           
           

            $maternity_benefit = db_select('labour_factory_statcell_annual_report_attach_maternity_t1', 'a'); 
            $maternity_benefit->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
            $maternity_benefit->condition('b.inspector_id',trim($uid),'=');
            $maternity_benefit->condition('b.report_year',trim($thisYear),'=');
           

            $maternity_benefit->fields('a',array('case_pending_at_end_4_c'));

            $maternity_benefit_result = $maternity_benefit->execute();
            $result_maternity_benefit=$maternity_benefit_result->fetchAssoc();

		    $case_pending_at_end_4_c=$result_maternity_benefit['case_pending_at_end_4_c'];


		    $maxresult_mtb=db_query('select  max(maternity_row_id) maxsl from labour_factory_statcell_annual_report_attach_maternity_t1');	
	        $result_mtb=$maxresult_mtb->fetchAssoc();
	        $max_sl_number_mtb = trim($result_mtb['maxsl']); 
            if($max_sl_number_mtb==0){$querystring_mtb=1;	}else{ $querystring_mtb=$max_sl_number_mtb+1; }
		    $maternity_row_id=$querystring_mtb;

 $fieldsE_mtb = array('maternity_row_id' => $maternity_row_id, 'annual_inspection_id' =>$autoGENNO ,'case_pending_at_beginning_4_a' => $case_pending_at_end_4_c);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_maternity_t1')->fields($fieldsE_mtb)->execute();



                 
                       // end tab 12 maternity benefit


                         // begin tab 12 Payment of wages



            $payment_wages = db_select('labour_factory_statcell_annual_report_attach_wages_t1', 'a'); 
            $payment_wages->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
            $payment_wages->condition('b.inspector_id',trim($uid),'=');
            $payment_wages->condition('b.report_year',trim($thisYear),'=');
           

            $payment_wages->fields('a',array('case_pending_at_end_3_c','app_pending_at_end_4_h'));

            $payment_wages_result = $payment_wages->execute();
            $result_payment_wages=$payment_wages_result->fetchAssoc();

		    $case_pending_at_end_3_c=!empty($result_payment_wages['case_pending_at_end_3_c']) ? trim($result_payment_wages['case_pending_at_end_3_c']) : 0;
		    $app_pending_at_end_4_h=!empty($result_payment_wages['app_pending_at_end_4_h']) ?  trim($result_payment_wages['app_pending_at_end_4_h']) : 0 ;




		      
               
                   $mr_before_pw_act = db_select('labour_factory_statcell_form_5_t13', 'a');

                   $mr_before_pw_act->InnerJoin('labour_factory_statcell_form_5', 'b', 'a.monthly_form_id=b.monthly_form_id');
                   $mr_before_pw_act->condition('b.inspector_id',trim($uid),'=');
                   $mr_before_pw_act->condition('b.report_from_date',trim($from),'>=');
                   $mr_before_pw_act->condition('b.report_to_date',trim($to),'<=');
                   $mr_before_pw_act->condition('b.status','FS','=');
                   $mr_before_pw_act->addExpression('COALESCE(count(pw_act_name_of_factory),0)', 'no_of_app');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_persons_involved), 0)', 'pw_act_persons_involved');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_amount_unpaid_wages),0)', 'pw_act_amount_unpaid_wages');
                   $mr_before_pw_act->addExpression('COALESCE(sum(pw_act_amount_unauthorized_deduction),0)',
                  'pw_act_amount_unauthorized_deduction');

                  $mr_before_pw_act->addExpression("string_agg(pw_act_name_of_factory, ';')", "pw_act_name_of_factory");
                 

                  $mr_before_pw_act_result = $mr_before_pw_act->execute(); 
    
                  $result_before_pw_act=$mr_before_pw_act_result->fetchAssoc();

                  $pw_act_name_of_factory=$result_before_pw_act['pw_act_name_of_factory'];
                  $pw_act_persons_involved=$result_before_pw_act['pw_act_persons_involved'] ;
                  $pw_act_amount_unpaid_wages= $result_before_pw_act['pw_act_amount_unpaid_wages'] ;
                  $pw_act_amount_unauthorized_deduction=$result_before_pw_act['pw_act_amount_unauthorized_deduction'] ;

                  $no_of_app=$result_before_pw_act['no_of_app'] ; 
              

		       
       






		    $maxresult_pw=db_query('select  max(wages_row_id) maxsl from labour_factory_statcell_annual_report_attach_wages_t1');	
	        $result_pw=$maxresult_pw->fetchAssoc();
	        $max_sl_number_pw = trim($result_pw['maxsl']); 
            if($max_sl_number_pw==0){$querystring_pw=1;	}else{ $querystring_pw=$max_sl_number_pw+1; }
		    $pw_row_id=$querystring_pw;

 $fieldsE_mtb = array('wages_row_id' => $pw_row_id, 'annual_inspection_id' =>$autoGENNO ,'case_pending_at_beginning_3_a' => $case_pending_at_end_3_c,


'factories_name_4_a' => $pw_act_name_of_factory, 'application_filed_4_b' => $no_of_app, 'person_involved_4_c' => $pw_act_persons_involved, 'wages_claimed_4_d' => $pw_act_amount_unpaid_wages, 'deduction_claimed_4_e' => $pw_act_amount_unauthorized_deduction, 'app_pending_at_beginning_4_f' => $app_pending_at_end_4_h);
		  
		   
     db_insert('labour_factory_statcell_annual_report_attach_wages_t1')->fields($fieldsE_mtb)->execute();


                            // end tab 12 payment of wages










                     


              


                  

	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/annual-report/step1/'.encryption_decryption_fun('encrypt',$autoGENNO);
	           
	             drupal_goto($full_base);

	         }

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report-list';

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
          '#title' => t(' <b>Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.' </b><br><br><font color="DarkGreen"><b> Inspection (A)   </b></font>'),
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
		       '#prefix' => '<table  class="table" border="1"><tr><td rowspan="4" >', 
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
		       '#prefix' => '<table class="table" border="1"><tr><td rowspan="4" >', 
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
		       '#prefix' => '<table class="table" border="1"><tr><td rowspan="2" >', 
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
		       '#prefix' => '<table class="table" border="1"><tr><td colspan="5" >', 
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


         global $base_root, $base_path , $full_base;




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
	           
	              drupal_set_message(t($message));
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
		
		
 
		
				
	
														
														  
	       