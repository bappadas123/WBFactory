<?php
function month_report_step4( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

      drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
      drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');


     $options_classification = array(0 => " Select  ") + an_classification_option();



     $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step4field'] = array(
          '#title' => t('<font color="DarkGreen"><b> '.$get_info_montly_report.' 4(a). Detail of fatal & serious accidents  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

 $form['step4field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );

       /* $step4_stepa_query = db_select('labour_factory_statcell_form_5_t4a', 'a');
       
        $step4_stepa_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step4_stepa_query->fields('a',array('acc_det_name_of_factory','acc_det_address_of_factory',
        'acc_det_name_of_deceased_injured','acc_det_date_of_accident','classification_code'));
        $step4_stepa_query_result = $step4_stepa_query->execute(); 
    
       $result_step4_a=$step4_stepa_query_result->fetchAssoc();*/



     $form['step4field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;" >', 
           '#markup'=>'<b> Name of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

            $form['step4field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Address of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );  

               $form['step4field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name(s) of the deceased / injured  </b>',

              '#suffix'=>'</td>',
     
     
           );
            $form['step4field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Date of accident  </b>',

              '#suffix'=>'</td>',
     
     
           );  
              $form['step4field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Accident classification  </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

            $form['step4field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
            '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
             // '#default_value' =>$result_step4_a['acc_det_name_of_factory']
     
     
           );
          
          $form['step4field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
            //  '#default_value' =>$result_step4_a['acc_det_address_of_factory']
     
     
           );

          $form['step4field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
           //   '#default_value' =>$result_step4_a['acc_det_name_of_deceased_injured']
     
     
           );

          $form['step4field']['fourvalue'] = array
              (
           '#prefix' => ' <td   >', 
          
          '#type' => 'textfield',
            '#size' => 12,
            '#attributes' => array('class' => array('datepicker_retify')),
            '#suffix'=>'</td>',
            //  '#default_value' =>$result_step4_a['acc_det_date_of_accident']
     
     
           );

              $form['step4field']['fivevalue'] = array
              (
               '#prefix' => ' <td  >', 
          
              '#type' => 'select',
              '#options' => $options_classification,
     
          //  '#default_value' => isset($form_state['values']['fivevalue']) ? $form_state['values']['fivevalue'] : $result_step4_a['classification_code'] ,

            '#suffix'=>'</td></tr></table>',
     
     
           );



$form['step4field']['submit_button']          = array(
                                 
                                '#prefix' => '<div style="text-align:center;" >',
                                '#suffix'=>'</div>', 
                              
                              
                               // '#submit' => array('mr_step4_parta_save'),
                               '#type' => 'button',
                              '#event' => 'click',

                              '#default_value' => 'ADD 1  ',
                              '#ajax' => array(
                              'callback' => 'add_step4_parta',
                              'wrapper' => 'part4a_div',
                              'method' => 'html',
                              'effect' => 'fade'
                               )

                                );


       $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t4a a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      
       <th > Name of the Factory</th>
      <th >Address of the Factory</th>
       
     <th >Name(s) of the deceased / injured</th>

     <th >Date of accident</th>
       
     <th >Accident classification</th>
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fouradel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$acc_details_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
       
     
                $output1.= "<td>".$acc_det_name_of_factory."</td>";
                $output1.= "<td>".$squan->acc_det_address_of_factory."</td>";
                $output1.= "<td>".$squan->acc_det_name_of_deceased_injured."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->acc_det_date_of_accident))."</td>";

                 $output1.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
                
                
                $output1.= "<td >".$del_preper."</td>";
      
              
              $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
   $form['step4field']['prpersonlista'] = array(
    '#prefix' => '<div align="left" id="part4a_div">'.$output1,
    '#suffix' => '</div>',
       
  );




        $form['step4Bfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  4(b). Detail of Non fatal accidents  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

        /*  $step4_stepb_query = db_select('labour_factory_statcell_form_5_t4b', 'b');
       
        $step4_stepb_query->condition('b.monthly_form_id',trim($filenumber),'=');
      
    
        $step4_stepb_query->fields('b',array('classification_code','type_of_industry',
        'injured_adult_male','injured_adult_female','injured_adult_male','injured_adult_female','injured_ado_male','injured_ado_female','injured_child_male','injured_child_female'));
        $step4_stepb_query_result = $step4_stepb_query->execute(); 
    
       $result_step4_b=$step4_stepb_query_result->fetchAssoc();*/

 $form['step4Bfield']['4bone'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;" rowspan="2" >', 
           '#markup'=>'<b> Accident classification  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step4Bfield']['4btwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2" >', 
           '#markup'=>'<b> Type of Industry  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step4Bfield']['4bthree'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="6" >', 
           '#markup'=>'<b> No. of Injured Person  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );


              $form['step4Bfield']['4bthreeOne'] = array
              (
           '#prefix' => '<tr><td  style="text-align:center;"  >', 
           '#markup'=>'<b> Adult Male  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step4Bfield']['4bthreeTwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Adult Female  </b>',

              '#suffix'=>'</td>',
     
     
           );
       
        $form['step4Bfield']['4bthreeThree'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Adolescent Male  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step4Bfield']['4bthreeFour'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Adolescent Female  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step4Bfield']['4bthreeFive'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Child Male  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step4Bfield']['4bthreeSix'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Child Female  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
     
           $form['step4Bfield']['fbonevalue'] = array
              (
           '#prefix' => '<tr> <td   >', 
          
         

              '#suffix'=>'</td>',

              '#type' => 'select',
              '#options' => $options_classification,
             //  '#default_value' => isset($form_state['values']['fbonevalue']) ? $form_state['values']['fbonevalue'] : $result_step4_b['classification_code'] ,

     
     
           );
          
          

            $form['step4Bfield']['fbtwovalue'] = array
              (
              
           '#prefix' => ' <td   >', 
          
          '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

           '#suffix'=>'</td>',
         //    '#default_value' =>$result_step4_b['type_of_industry']
     
     
     
           );
           $form['step4Bfield']['fbthreevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
       // '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
           );
           $form['step4Bfield']['fbfourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
           // '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
           $form['step4Bfield']['fbfivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
           // '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
           $form['step4Bfield']['fbsixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
           // '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );

           $form['step4Bfield']['fbsevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
           //'#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
           $form['step4Bfield']['fbeightvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td></tr></table>',
         //'#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
     
           );

           $form['step4Bfield']['submit_button_2']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                              //  '#type'         =>'submit',
                              //  '#value'        =>t(' Add 2 '),
                               //'#submit' => array('mr_step4_partb_save'),

                               '#type' => 'button',
                              '#event' => 'click',

                              '#default_value' => 'ADD 2  ',
                              '#ajax' => array(
                              'callback' => 'add_step4_partb',
                              'wrapper' => 'part4b_div',
                              'method' => 'html',
                              'effect' => 'fade'
                               )




                                );



           $output2='';
      if(trim($filenumber)){
      $query_tab_4_b=db_query('select  *  from labour_factory_statcell_form_5_t4b a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_4_b->rowCount() > 0) 
              { 
     $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      
       <th > Accident classification</th>
      <th >Type of Industry </th>
       
     <th >Adult Male</th>

     <th >Adult Female</th>
       
     <th >Adolescent Male</th>
     
     <th >Adolescent Female</th>
    <th >Child Male</th>
    <th >Child Female</th>
    <th >Delete</th>
    </tr>";  
        $i=0;
    foreach($query_tab_4_b as $squan) {
      $i++;
         // $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
            $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fourbdel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$squan->nf_acc_details_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper2=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output2 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output2 .= "<tr bgcolor=\"#FEFEF2\">";
        }
       
     
                $output2.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
                $output2.= "<td>".$squan->type_of_industry."</td>";
                $output2.= "<td>".$squan->injured_adult_male."</td>";
                $output2.= "<td>".$squan->injured_adult_female."</td>";

              $output2.= "<td>".$squan->injured_ado_male."</td>";
              $output2.= "<td>".$squan->injured_ado_female."</td>";

              $output2.= "<td>".$squan->injured_child_male."</td>";
              $output2.= "<td>".$squan->injured_child_female."</td>";
                
                
                
                $output2.= "<td >".$del_preper2."</td>";
      
              
              $output2 .= "</tr>";
            }
              $output2 .= "</table>";
        
      

  
     }
  }
   $form['step4Bfield']['prpersonlistb'] = array(
    '#prefix' => '<div align="left" id="part4b_div">'.$output2,
    '#suffix' => '</div>',
       
  );

             return $form; 

     }


    


     function an_classification_option() {
    $blk="SELECT * FROM {labour_factory_accident_classification_mst} ORDER BY classification_class";
  
    $state_query=db_query($blk);

   $options        = array();
  
   foreach($state_query as $state_result) {
    
    $options[$state_result->accident_classification_id] =$state_result->classification_class.'-'.$state_result->classification_details;  
  
  }
  
  
  
   
       return $options;
    
     }
      
   
  

     function add_step4_parta($form , $form_state) { 
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $val=$form_state['values'];



  $monthlyformid=trim($val['monthlyformid']);
    
  $onevalue=trim($val['onevalue']); if(!$onevalue)  $onevalue= NULL;   
  $twovalue=trim($val['twovalue']); if(!$twovalue)  $twovalue= NULL;   
  $threevalue=trim($val['threevalue']); if(!$threevalue) $threevalue= NULL;
  $fourvalue=trim($val['fourvalue']); 
  if(!$fourvalue)  
    $fourvalue= NULL; 
    else
  $fourvalue= date('Y-m-d', strtotime($fourvalue));    

  

  $fivevalue=trim($val['fivevalue']); if(!$fivevalue)  $fivevalue= NULL;   
        

     // return  $fourvalue;
  
   
      


     $txn = db_transaction();

        try {
     
   
   
            $maxresult=db_query('select  max(acc_details_id) maxsl from labour_factory_statcell_form_5_t4a');  
            $result=$maxresult->fetchAssoc();
            $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
             $autoGENNO=$querystring;


      $fieldsE = array('acc_details_id' =>$autoGENNO, 'monthly_form_id' => $monthlyformid, 'acc_det_name_of_factory' => $onevalue, 'acc_det_address_of_factory' => $twovalue,  'acc_det_name_of_deceased_injured' => $threevalue, 'acc_det_date_of_accident' => $fourvalue, 'classification_code' => $fivevalue );
      
        db_insert('labour_factory_statcell_form_5_t4a')->fields($fieldsE)->execute(); 
   
   
  $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t4a a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($monthlyformid) ));
      //if($query_tab_1_c->rowCount() > 0) 
             // { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      
       <th > Name of the Factory</th>
      <th >Address of the Factory</th>
       
     <th >Name(s) of the deceased / injured</th>

     <th >Date of accident</th>
       
     <th >Accident classification</th>
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fouradel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$acc_details_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
       
     
                $output1.= "<td>".$acc_det_name_of_factory."</td>";
                $output1.= "<td>".$squan->acc_det_address_of_factory."</td>";
                $output1.= "<td>".$squan->acc_det_name_of_deceased_injured."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->acc_det_date_of_accident))."</td>";

                 $output1.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
                
                
                $output1.= "<td >".$del_preper."</td>";
      
              
              $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     



    }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $output1 = ' DATA NOT INSERT';
  }  
  


                          drupal_get_messages(error);
                      return $output1;
                      exit;
                          
                          }




     function add_step4_partb($form , $form_state) {  
       $val=$form_state['values'];



     $monthlyformid=trim($val['monthlyformid']);
    
 
  $fbonevalue=trim($val['fbonevalue']); if(!$fbonevalue)  $fbonevalue= NULL;   
  $fbtwovalue=trim($val['fbtwovalue']); if(!$fbtwovalue)  $fbtwovalue= NULL; 

   if(trim($val['fbthreevalue']) && !preg_match('/^[0-9]+$/',trim($val['fbthreevalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 
   elseif(trim($val['fbfourvalue']) && !preg_match('/^[0-9]+$/',trim($val['fbfourvalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 
   elseif(trim($val['fbfivevalue']) && !preg_match('/^[0-9]+$/',trim($val['fbfivevalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 
   elseif(trim($val['fbsixvalue']) && !preg_match('/^[0-9]+$/',trim($val['fbsixvalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 
   elseif(trim($val['fbsevenvalue']) && !preg_match('/^[0-9]+$/',trim($val['fbsevenvalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 
   elseif(trim($val['fbeightvalue']) && !preg_match('/^[0-9]+$/',trim($val['fbeightvalue']))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   No. of Injured Person (male , female) should be   number <b>    </font>";
    exit;  
   } 

  $fbthreevalue=trim($val['fbthreevalue']); if(!$fbthreevalue) $fbthreevalue= NULL;
  $fbfourvalue=trim($val['fbfourvalue']); if(!$fbfourvalue)  $fbfourvalue= NULL;  
  $fbfivevalue=trim($val['fbfivevalue']); if(!$fbfivevalue)  $fbfivevalue= NULL;  


  $fbsixvalue=trim($val['fbsixvalue']); if(!$fbsixvalue)  $fbsixvalue= NULL;
  $fbsevenvalue=trim($val['fbsevenvalue']); if(!$fbsevenvalue)  $fbsevenvalue= NULL;
  $fbeightvalue=trim($val['fbeightvalue']); if(!$fbeightvalue)  $fbeightvalue= NULL;  
        


  
   
      


     $txn = db_transaction();

        try {
     
   
   
             $maxresult=db_query('select  max(nf_acc_details_id) maxsl from labour_factory_statcell_form_5_t4b');  
            $result=$maxresult->fetchAssoc();
            $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
             $autoGENNO=$querystring;


      $fieldsE = array('nf_acc_details_id' =>$autoGENNO, 'monthly_form_id' => $monthlyformid, 'classification_code' => $fbonevalue, 'type_of_industry' => $fbtwovalue,  'injured_adult_male' => $fbthreevalue, 'injured_adult_female' => $fbfourvalue, 'injured_ado_male' => $fbfivevalue , 'injured_ado_female' => $fbsixvalue , 'injured_child_male' => $fbsevenvalue , 'injured_child_female' => $fbeightvalue);
      
        db_insert('labour_factory_statcell_form_5_t4b')->fields($fieldsE)->execute(); 
   
   
  
          $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t4b a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($monthlyformid) ));
    
     $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      
       <th > Accident classification</th>
      <th >Type of Industry </th>
       
     <th >Adult Male</th>

     <th >Adult Female</th>
       
     <th >Adolescent Male</th>
     
     <th >Adolescent Female</th>
    <th >Child Male</th>
    <th >Child Female</th>
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
         // $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
            $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fourbdel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$squan->nf_acc_details_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper2=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output2 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output2 .= "<tr bgcolor=\"#FEFEF2\">";
        }
       
     
                $output2.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
                $output2.= "<td>".$squan->type_of_industry."</td>";
                $output2.= "<td>".$squan->injured_adult_male."</td>";
                $output2.= "<td>".$squan->injured_adult_female."</td>";

              $output2.= "<td>".$squan->injured_ado_male."</td>";
              $output2.= "<td>".$squan->injured_ado_female."</td>";

              $output2.= "<td>".$squan->injured_child_male."</td>";
              $output2.= "<td>".$squan->injured_child_female."</td>";
                
                
                
                $output2.= "<td >".$del_preper2."</td>";
      
              
              $output2 .= "</tr>";
            }
              $output2 .= "</table>";      
              
      

    }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $output2 = ' DATA NOT INSERT';
  }  
  


          drupal_get_messages(error);
          return $output2;
          exit;
                          
      }



     function step4a_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t4a')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('acc_details_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step4/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

  function step4b_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    
     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t4b')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('nf_acc_details_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step4/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }




     ?>