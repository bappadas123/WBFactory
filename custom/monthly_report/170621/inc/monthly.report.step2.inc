
<?php
function month_report_step2( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));


        $step2_select_query = db_select('labour_factory_statcell_form_5_6_7_t2', 'a');
       
        $step2_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step2_select_query->fields('a',array('visit_pwa','visit_mba','visit_msihcr','visit_car','visit_clpra','visit_rest_interval','visit_bef_after_legal_hours','visit_sunday_holiday','visit_approval_of_plan','visit_reg_licence','visit_collection_statistics','visit_enq_complaints','visit_court_attendance','visit_attn_seminar_meeting','visit_to_closed_factory','visit_others','visit_total'));
        $step2_select_query_result = $step2_select_query->execute(); 
    
    $result_step2=$step2_select_query_result->fetchAssoc();
    //$ado_no_of_accidents_fatal=$result_step2['ado_no_of_accidents_fatal'];
   // print 
       
   $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['#attached']['js'] = array(drupal_get_path('module', 'monthly_report') . '/js/monthlyreport.js',);



    $form['step2field'] = array(
          '#title' => t('<font color="DarkGreen"><b> '.$get_info_montly_report.' 2. No. of Special Visit  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );


     $form['step2field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );


     $form['step2field']['oneB'] = array
              (
           '#prefix' => '<table class="table"  border="1"><tr><td colspan="5" style="text-align:center;" >', 
           '#markup'=>'<b> Exclusively <br> under  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


            $form['step2field']['twoB'] = array
              (
           '#prefix' => '<td rowspan="2" style="text-align:center;">', 
           '#markup'=>'<b> During rest <br> Interval </b>',

              '#suffix'=>'</td>',
     
     
           ); 


             $form['step2field']['threeB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> Before or after <br>legal hours  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step2field']['fourB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> On Sundays <br>and <br> Holidays  </b>',

              '#suffix'=>'</td>',
     
     
           );


              $form['step2field']['fiveB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For approval <br> of plans  </b>',

              '#suffix'=>'</td>',
     
     
           );
         
        $form['step2field']['sixB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For registration <br> and <br>licence  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step2field']['sevenB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For collections <br> of statistic  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step2field']['eightB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For enquiry <br> into <br> complaints  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step2field']['nineB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For court<br> attendance  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step2field']['tenB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> For attending <br> safety seminars,<br> meetings etc  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step2field']['elevanB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> To closed <br> factories  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step2field']['twelveB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> Others  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step2field']['thirtennB'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> Total  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

              


           $form['step2field']['oneBone'] = array
              (
           '#prefix' => '<tr><td  style="text-align:center;" >', 
           '#markup'=>'<b> PWA  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step2field']['oneBtwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> MBA  </b>',

              '#suffix'=>'</td>',
     
     
           );
           $form['step2field']['oneBthree'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> MSIHCR  </b>',

              '#suffix'=>'</td>',
     
     
           );  
               $form['step2field']['oneBfour'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> CAR  </b>',

              '#suffix'=>'</td>',
     
     
           );  

              $form['step2field']['oneBfive'] = array
              (
              '#prefix' => '<td  style="text-align:center;" >', 
               '#markup'=>'<b> CL(P&R)A  </b>',

               '#suffix'=>'</td></tr>',
     
     
           );    
       $form['step2field']['oneBonevalue'] = array
              (
           '#prefix' => ' <tr><td  >', 
           '#type' => 'textfield',
                '#size' => 5,
         '#default_value' =>$result_step2['visit_pwa'] ,
            '#suffix'=>'</td>',
              '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );
               $form['step2field']['oneBtwovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_mba'],
              '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );

             $form['step2field']['oneBthreevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_msihcr'],
              '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );  

               $form['step2field']['oneBfourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
          '#default_value' =>$result_step2['visit_car'],
            '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 

            $form['step2field']['oneBfivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_clpra'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
     
           );   

           $form['step2field']['twoBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
          '#default_value' =>$result_step2['visit_rest_interval'],
            '#attributes' => array("onkeyup" => "addNospecial();"), 
     
           ); 
           $form['step2field']['threeBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_bef_after_legal_hours'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 
           $form['step2field']['fourBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_sunday_holiday'],
              '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 
            $form['step2field']['fiveBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_approval_of_plan'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 
           $form['step2field']['sixBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_reg_licence'],
              '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );
            $form['step2field']['sevenBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['visit_collection_statistics'],
                '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 

           $form['step2field']['eightBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_enq_complaints'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );  
           $form['step2field']['nineBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_court_attendance'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );  
           $form['step2field']['tenBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_attn_seminar_meeting'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );  
            $form['step2field']['elevanBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_to_closed_factory'],
               '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 
           $form['step2field']['tweleveBvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['visit_others'],
                '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           ); 
           $form['step2field']['thirteenBvalue'] = array
              (
             '#prefix' => ' <td  >', 
             '#type' => 'textfield',
             //'#size' => 8,

            '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step2['visit_total'],
              // '#attributes' => array("onkeyup" => "addNospecial();"), 
     
     
           );

              $form['step2field']['fourteenBvalue'] = array
              (
            '#prefix' => '<tr> <td colspan="17"  >', 
          

             '#markup'=>'<b> [PWA-Payment of Wages Act, MBA-Maternity Benefit Act, MSIHCR-Manufacture, Storage & import of Hazaedous Chemical Rules; <br> CAR-Chemical Accident(Energy Planning, Preparedness & Response) Rules: CL(P&R)A-Child Labour (Prevention & regulation) Act.]  </b>',    

            '#suffix'=>'</td></tr></table>',
     
     
           );

            $form['step2field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );


    return $form;
					
	}

  function month_report_step2_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);  
//exit;
 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  $oneBonevalue=trim($val['oneBonevalue']);  if(!$oneBonevalue) $oneBonevalue= NULL;         
  $oneBtwovalue=trim($val['oneBtwovalue']); if(!$oneBtwovalue) $oneBtwovalue= NULL;
  $oneBthreevalue=trim($val['oneBthreevalue']); if(!$oneBthreevalue) $oneBthreevalue= NULL;
  $oneBfourvalue=trim($val['oneBfourvalue']); if(!$oneBfourvalue) $oneBfourvalue= NULL;
  $oneBfivevalue=trim($val['oneBfivevalue']); if(!$oneBfivevalue) $oneBfivevalue= NULL;
 



  $twoBvalue=trim($val['twoBvalue']);  if(!$twoBvalue) $twoBvalue= NULL;         
  $threeBvalue=trim($val['threeBvalue']); if(!$threeBvalue) $threeBvalue= NULL;
  $fourBvalue=trim($val['fourBvalue']); if(!$fourBvalue) $fourBvalue= NULL;
  $fiveBvalue=trim($val['fiveBvalue']); if(!$fiveBvalue) $fiveBvalue= NULL;
  $sixBvalue=trim($val['sixBvalue']); if(!$sixBvalue) $sixBvalue= NULL;
  $sevenBvalue=trim($val['sevenBvalue']);   if(!$sevenBvalue) $sevenBvalue= NULL;
  $eightBvalue=trim($val['eightBvalue']); if(!$eightBvalue) $eightBvalue= NULL;
  $nineBvalue=trim($val['nineBvalue']); if(!$nineBvalue) $nineBvalue= NULL;

   $tenBvalue=trim($val['tenBvalue']); if(!$tenBvalue) $tenBvalue= NULL;
   $elevanBvalue=trim($val['elevanBvalue']); if(!$elevanBvalue) $elevanBvalue= NULL;
   $tweleveBvalue=trim($val['tweleveBvalue']); if(!$tweleveBvalue) $tweleveBvalue= NULL;
   $thirteenBvalue=trim($val['thirteenBvalue']); if(!$thirteenBvalue) $thirteenBvalue= NULL;


   $txn = db_transaction();
    try {


       $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_6_7_t2 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
             
        $query_update_A = db_update('labour_factory_statcell_form_5_6_7_t2');
        $query_update_A->fields(array(
      'visit_pwa' =>$oneBonevalue,'visit_mba' =>$oneBtwovalue, 'visit_msihcr' => $oneBthreevalue, 'visit_car' => $oneBfourvalue, 'visit_clpra' => $oneBfivevalue, 'visit_rest_interval' => $twoBvalue, 'visit_bef_after_legal_hours' => $threeBvalue, 'visit_sunday_holiday' => $fourBvalue,


    'visit_approval_of_plan' => $fiveBvalue, 'visit_reg_licence' => $sixBvalue , 'visit_collection_statistics' => $sevenBvalue
     , 'visit_enq_complaints' => $eightBvalue , 'visit_court_attendance' => $nineBvalue , 'visit_attn_seminar_meeting' => $tenBvalue ,

     'visit_to_closed_factory' => $elevanBvalue , 'visit_others' => $tweleveBvalue, 'visit_total' => $thirteenBvalue




   ));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute();  

          }
          else

          {

  
            $maxresult=db_query('select  max(visit_id) maxsl from labour_factory_statcell_form_5_6_7_t2'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
        $rowid=$querystring;

 $fieldsA = array('visit_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'form_type' =>'GENERAL',  'visit_pwa' =>$oneBonevalue,'visit_mba' =>$oneBtwovalue, 'visit_msihcr' => $oneBthreevalue, 'visit_car' => $oneBfourvalue, 'visit_clpra' => $oneBfivevalue, 'visit_rest_interval' => $twoBvalue, 'visit_bef_after_legal_hours' => $threeBvalue, 'visit_sunday_holiday' => $fourBvalue,


    'visit_approval_of_plan' => $fiveBvalue, 'visit_reg_licence' => $sixBvalue , 'visit_collection_statistics' => $sevenBvalue
     , 'visit_enq_complaints' => $eightBvalue , 'visit_court_attendance' => $nineBvalue , 'visit_attn_seminar_meeting' => $tenBvalue ,

     'visit_to_closed_factory' => $elevanBvalue , 'visit_others' => $tweleveBvalue, 'visit_total' => $thirteenBvalue);

             db_insert('labour_factory_statcell_form_5_6_7_t2')->fields($fieldsA)->execute(); 




   

             }

               $full_base=$base_root.$base_path.'admin/monthly-report/step2/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
                      drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step2/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
                      drupal_set_message(t($message));
             
               drupal_goto($full_base);
  
     }
  }

  ?>