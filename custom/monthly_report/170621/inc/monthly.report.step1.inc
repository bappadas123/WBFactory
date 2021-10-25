<?php
function month_report_step1( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

	  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	 //$output='step1';
	// print $filenumber;
	// exit;


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
	
	      $step1_select_query = db_select('labour_factory_statcell_form_5_6_7_t1', 'a');
       
          $step1_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
		
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
	}

	$form['#attached']['js'] = array(drupal_get_path('module', 'monthly_report') . '/js/monthlyreport.js',);	


   
    $get_info_montly_report=get_monthly_area_from_to_date($filenumber);
   



  $form['step1field'] = array(
          '#title' => t('<font color="DarkGreen"><b> '.$get_info_montly_report.'Inspection (A).  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
 $form['step1field']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );

	   $form['step1field']['monthlyformid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
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

		       '#attributes' => array("onkeyup" => "addIA('G');"),

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1field']['Gftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',

		        '#default_value' =>$g_nouv_regfac_2m_ii   ,
		       '#attributes' => array("onkeyup" => "addIA('G');"), 
	   
	   
           );
               $form['step1field']['Gfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		        '#default_value' =>$g_nouv_regfac_85    ,
		       '#attributes' => array("onkeyup" => "addIA('G');"),  
	   
	   
           );

              $form['step1field']['Gffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',

	           '#default_value' =>$g_nouv_unregfac_2m_i    ,
		       '#attributes' => array("onkeyup" => "addIA('G');"),
	   
           );
			 $form['step1field']['Gffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	      '#default_value' =>$g_nouv_unregfac_2m_ii   ,
		   '#attributes' => array("onkeyup" => "addIA('G');"),
	   
           );	

           $form['step1field']['Gfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	     '#default_value' =>$g_nouv_unregfac_85 ,
		   '#attributes' => array("onkeyup" => "addIA('G');"),
           );	

           $form['step1field']['Gfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		     '#default_value' =>$g_nouv_non_amendable ,
		     '#attributes' => array("onkeyup" => "addIA('G');"),      
	   
	   
           );	
            $form['step1field']['Gfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	      '#default_value' =>$g_nouv_total         
	   
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
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
	   
           );

                $form['step1field']['Hftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_regfac_2m_ii ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
           );
               $form['step1field']['Hfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	     '#default_value' =>$h_nouv_regfac_85  ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
           );

              $form['step1field']['Hffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_unregfac_2m_i  ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
           );
			 $form['step1field']['Hffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	        '#default_value' =>$h_nouv_unregfac_2m_ii  ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
           );	

           $form['step1field']['Hfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	          '#default_value' =>$h_nouv_unregfac_85 ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
	   
           );	

           $form['step1field']['Hfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	           '#default_value' =>$h_nouv_non_amendable ,
		       '#attributes' => array("onkeyup" => "addIA('H');"),
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

		         '#default_value' =>$mah_nouv_regfac_2m_i   ,
		       '#attributes' => array("onkeyup" => "addIA('M');"),
	   
	   
           );

                $form['step1field']['MAHftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	    '#default_value' =>$mah_nouv_regfac_2m_ii    ,
		       '#attributes' => array("onkeyup" => "addIA('M');"), 
	   
           );
               $form['step1field']['MAHfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	        '#default_value' =>$mah_nouv_regfac_85  ,
		       '#attributes' => array("onkeyup" => "addIA('M');"),  
	   
           );

              $form['step1field']['MAHffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	         '#default_value' =>$mah_nouv_unregfac_2m_i  ,
		       '#attributes' => array("onkeyup" => "addIA('M');"),   
	   
           );
			 $form['step1field']['MAHffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   '#default_value' =>$mah_nouv_unregfac_2m_ii   ,
		     '#attributes' => array("onkeyup" => "addIA('M');"), 
	   
           );	

           $form['step1field']['MAHfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',

	    '#default_value' =>$mah_nouv_unregfac_85    ,
		    '#attributes' => array("onkeyup" => "addIA('M');"),
	   
           );	

           $form['step1field']['MAHfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',

		       '#default_value' =>$mah_nouv_non_amendable ,  
		     
		       '#attributes' => array("onkeyup" => "addIA('M');"),  
	   
	   
           );	
            $form['step1field']['MAHfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
                '#default_value' =>$mah_nouv_total  ,    
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );

     // partB

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

 
      $form['step1Bfield']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );
   
    return $form; 

	}

	function month_report_step1_submit($form , $form_state) {	


         global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);  
//exit;
 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

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
  
  



   







  
    
    $txn = db_transaction();
	  try {


              $query_update_a_yes=db_query('select  * from labour_factory_statcell_form_5_6_7_t1 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
	     if($query_update_a_yes->rowCount() > 0) 
          {

           



        $query_update_A = db_update('labour_factory_statcell_form_5_6_7_t1');
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
										
										
										
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute();



      






          }
          else

          {

  
            $maxresult=db_query('select  max(inspection_id) maxsl from labour_factory_statcell_form_5_6_7_t1');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $rowid=$querystring;

 $fieldsA = array('inspection_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'g_nouv_regfac_2m_i' =>$Gfone,'g_nouv_regfac_2m_ii' =>$Gftwo, 'g_nouv_regfac_85' => $Gfthree, 'g_nouv_unregfac_2m_i' => $Gffour, 'g_nouv_unregfac_2m_ii' => $Gffive, 'g_nouv_unregfac_85' => $Gfsix, 'g_nouv_non_amendable' => $Gfseven, 'g_nouv_total' => $Gfeight,


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
		  
             db_insert('labour_factory_statcell_form_5_6_7_t1')->fields($fieldsA)->execute();	




   

             }


	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
                $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				  $full_base=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$monthly_form_id);
	           
	              drupal_set_message(t($message));
	              drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step1/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }
	
		 
		 
	
	 	}

	?>