<?php
function month_report_step8( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

   $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step8field'] = array(
          '#title' => t('<font color="DarkGreen"><b> '.$get_info_montly_report.' 8. Complaints  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

 $form['step8field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );

       $step8_select_query = db_select('labour_factory_statcell_form_5_t8', 'a');
       
        $step8_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step8_select_query->fields('a',array('compl_reg_no_rec_fa' ,
    'compl_reg_no_rec_pwa' ,
    'compl_reg_no_rec_mba' ,
    'compl_reg_no_rec_msihcr' ,
    'compl_reg_no_rec_car' ,
    'compl_reg_no_rec_clpra',
    'compl_unreg_no_rec_fa',
    'compl_unreg_no_rec_pwa',
    'compl_unreg_no_rec_mba',
    'compl_unreg_no_rec_msihcr' ,
    'compl_unreg_no_rec_car' ,
    'compl_unreg_no_rec_clpra',
    'compl_reg_no_inv_fa',
    'compl_reg_no_inv_pwa',
    'compl_reg_no_inv_mba' ,
    'compl_reg_no_inv_msihcr',
    'compl_reg_no_inv_car',
    'compl_reg_no_inv_clpra',
    'compl_unreg_no_inv_fa',
    'compl_unreg_no_inv_pwa' ,
    'compl_unreg_no_inv_mba',
    'compl_unreg_no_inv_msihcr' ,
    'compl_unreg_no_inv_car' ,
    'compl_unreg_no_inv_clpra',
    'compl_reg_no_settled_fa',
    'compl_reg_no_settled_pwa' ,
    'compl_reg_no_settled_mba',
    'compl_reg_no_settled_msihcr',
    'compl_reg_no_settled_car',
    'compl_reg_no_settled_clpra' ,
    'compl_unreg_no_settled_fa' ,
    'compl_unreg_no_settled_pwa' ,
    'compl_unreg_no_settled_mba' ,
    'compl_unreg_no_settled_msihcr',
    'compl_unreg_no_settled_car',
    'compl_unreg_no_settled_clpra',
    'compl_reg_violation_fa' ,
    'compl_reg_violation_pwa' ,
    'compl_reg_violation_mba',
    'compl_reg_violation_msihcr' ,
    'compl_reg_violation_car' ,
    'compl_reg_violation_clpra',
    'compl_unreg_violation_fa' ,
    'compl_unreg_violation_pwa' ,
    'compl_unreg_violation_mba' ,
    'compl_unreg_violation_msihcr' ,
    'compl_unreg_violation_car' ,
    'compl_unreg_violation_clpra',
    'compl_reg_remarks_fa' ,
    'compl_reg_remarks_pwa' ,
    'compl_reg_remarks_mba' ,
    'compl_reg_remarks_msihcr',
    'compl_reg_remarks_car' ,
    'compl_reg_remarks_clpra' ,
    'compl_unreg_remarks_fa' ,
    'compl_unreg_remarks_pwa' ,
    'compl_unreg_remarks_mba' ,
    'compl_unreg_remarks_msihcr',
    'compl_unreg_remarks_car',
    'compl_unreg_remarks_clpra' ));
    $step8_select_query_result = $step8_select_query->execute(); 
    
    $result_step8=$step8_select_query_result->fetchAssoc();
   
    


     $form['step8field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;" rowspan="2"  >', 
           '#markup'=>'<b> Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 




       $form['step8field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="6"   >', 
           '#markup'=>'<b> Registered  </b>',

              '#suffix'=>'</td>',
     
     
           );


               $form['step8field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="6" >', 
           '#markup'=>'<b> Unregistered  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
              
             $form['step8field']['twoone'] = array
              (
           '#prefix' => '<tr> <td  style="text-align:center;"   >', 
           '#markup'=>'<b> FA  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step8field']['twotwo'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> PWA  </b>',

              '#suffix'=>'</td>',
     
     
           );

      $form['step8field']['twothree'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> MBA  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step8field']['twofour'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> MSIHCR  </b>',

              '#suffix'=>'</td>',
     
     
           );
       $form['step8field']['twofive'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> CAR  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step8field']['twosix'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> CL(P&R)A   </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step8field']['threeone'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> FA   </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step8field']['threetwo'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> PWA   </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step8field']['threethree'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> MBA   </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step8field']['threefour'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> MSIHCR   </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step8field']['threefive'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> CAR   </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step8field']['threesix'] = array
              (
           '#prefix' => ' <td  style="text-align:center;"   >', 
           '#markup'=>'<b> CL(P&R)A   </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

           

            $form['step8field']['norecived'] = array
              (
           '#prefix' => ' <tr> <td  >', 
            '#markup'=>'<b> No. Received   </b>',
            '#suffix'=>'</td>',
     
     
           );

           $form['step8field']['norecivedone'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
             '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_rec_fa']
     
     
           );


           $form['step8field']['norecivedtwo'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_rec_pwa']
     
     
           );
            $form['step8field']['norecivedthree'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_rec_mba']
     
     
           );
      
        $form['step8field']['norecivedfour'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_no_rec_msihcr']
     
     
           );

            $form['step8field']['norecivedfive'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_no_rec_car']
     
     
           );
            $form['step8field']['norecivedsix'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_no_rec_clpra']
     
     
           );
           $form['step8field']['norecivedseven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_rec_fa']
     
     
           );
            $form['step8field']['norecivedeight'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_no_rec_pwa']
     
     
           );
            $form['step8field']['norecivednine'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_rec_mba']
     
     
           );
           $form['step8field']['norecivedten'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_no_rec_msihcr']
     
     
           );
           $form['step8field']['recivedeleven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
            '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_no_rec_car']
     
     
           );
            $form['step8field']['recivedtweleve'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td></tr>',
            '#default_value' =>$result_step8['compl_unreg_no_rec_clpra']
     
     
           );

            $form['step8field']['noinvst'] = array
              (
           '#prefix' => ' <tr> <td  >', 
            '#markup'=>'<b> No. investigated   </b>',
            '#suffix'=>'</td>',
     
     
           );

           $form['step8field']['noinvstone'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_no_inv_fa']
     
     
           );


           $form['step8field']['noinvsttwo'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_inv_pwa']
     
     
           );
            $form['step8field']['noinvstthree'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_inv_mba']
     
     
           );
      
        $form['step8field']['noinvstfour'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_no_inv_msihcr']
     
     
           );

            $form['step8field']['noinvstfive'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_inv_car']
     
     
           );
            $form['step8field']['noinvstsix'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_no_inv_clpra']
     
     
           );
           $form['step8field']['noinvstseven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_inv_fa']
     
     
           );
            $form['step8field']['noinvsteight'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_inv_pwa']
     
     
           );
            $form['step8field']['noinvstnine'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_inv_mba']
     
     
           );
           $form['step8field']['noinvstten'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_inv_msihcr']
     
     
           );
           $form['step8field']['noinvsteleven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_no_inv_car']
     
     
           );
            $form['step8field']['noinvsttweleve'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step8['compl_unreg_no_inv_clpra']
     
     
           );

           $form['step8field']['noset'] = array
              (
           '#prefix' => ' <tr> <td  >', 
            '#markup'=>'<b> No. settled   </b>',
            '#suffix'=>'</td>',
     
     
           );

           $form['step8field']['nosetone'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_no_settled_fa']
     
     
           );


           $form['step8field']['nosettwo'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_no_settled_pwa']
     
     
           );
            $form['step8field']['nosetthree'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_settled_mba']
     
     
           );
      
        $form['step8field']['nosetfour'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_no_settled_msihcr']
     
     
           );

            $form['step8field']['nosetfive'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
               '#default_value' =>$result_step8['compl_reg_no_settled_car']
     
     
           );
            $form['step8field']['nosetsix'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_no_settled_clpra']
     
     
           );
           $form['step8field']['nosetseven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_settled_fa']
     
     
           );
            $form['step8field']['noseteight'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
           '#default_value' =>$result_step8['compl_unreg_no_settled_pwa']
     
     
           );
            $form['step8field']['nosetnine'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_settled_mba']
     
     
           );
           $form['step8field']['nosetten'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_settled_msihcr']
     
     
     
           );
           $form['step8field']['noseteleven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_no_settled_car']
     
     
           );
            $form['step8field']['nosettweleve'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step8['compl_unreg_no_settled_clpra']
     
     
           );

           $form['step8field']['vioobs'] = array
              (
           '#prefix' => ' <tr> <td  >', 
            '#markup'=>'<b> Violation observed   </b>',
            '#suffix'=>'</td>',
     
     
           );

           $form['step8field']['vioobsone'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_violation_fa']
     
           );


           $form['step8field']['vioobstwo'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_violation_pwa']
     
     
           );
            $form['step8field']['vioobsthree'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_violation_mba']
     
     
           );
      
        $form['step8field']['vioobsfour'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_violation_msihcr']
     
     
           );

            $form['step8field']['vioobsfive'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_reg_violation_car']
     
     
           );
            $form['step8field']['vioobssix'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_violation_clpra']
     
     
           );
           $form['step8field']['vioobsseven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_violation_fa']
     
     
           );
            $form['step8field']['vioobseight'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_unreg_violation_pwa']
     
     
           );
            $form['step8field']['vioobsnine'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_violation_mba']
     
     
           );
           $form['step8field']['vioobsten'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_violation_msihcr']
     
     
           );
           $form['step8field']['vioobseleven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_unreg_violation_car']
     
     
           );
            $form['step8field']['vioobstweleve'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step8['compl_unreg_violation_clpra']
     
     
           );

            $form['step8field']['remarks'] = array
              (
           '#prefix' => ' <tr> <td  >', 
            '#markup'=>'<b> Remarks   </b>',
            '#suffix'=>'</td>',
     
     
           );

           $form['step8field']['remarksone'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_remarks_fa']
     
     
           );


           $form['step8field']['remarkstwo'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_remarks_pwa']
     
     
           );
            $form['step8field']['remarksthree'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_remarks_mba']
     
     
           );
      
        $form['step8field']['remarksfour'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_reg_remarks_msihcr']
     
     
           );

            $form['step8field']['remarksfive'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_remarks_car']
     
     
           );
            $form['step8field']['remarkssix'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_reg_remarks_clpra']
     
           );
           $form['step8field']['remarksseven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_remarks_fa']
     
     
           );
            $form['step8field']['remarkseight'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_remarks_pwa']
     
     
           );
            $form['step8field']['remarksnine'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step8['compl_unreg_remarks_mba']
     
     
           );
           $form['step8field']['remarksten'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step8['compl_unreg_remarks_msihcr']
     
     
           );
           $form['step8field']['remarkseleven'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step8['compl_unreg_remarks_car']
     
     
           );
            $form['step8field']['remarkstweleve'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td></tr></table>',
             '#default_value' =>$result_step8['compl_unreg_remarks_clpra']
     
     
           );
        $form['step8field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );

           return $form;
         }



      function month_report_step8_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 



  $norecivedone=trim($val['norecivedone']);  if(!$norecivedone) $norecivedone= NULL;         
  $norecivedtwo=trim($val['norecivedtwo']); if(!$norecivedtwo) $norecivedtwo= NULL;
  $norecivedthree=trim($val['norecivedthree']); if(!$norecivedthree) $norecivedthree= NULL;
  $norecivedfour=trim($val['norecivedfour']); if(!$norecivedfour) $norecivedfour= NULL;
  $norecivedfive=trim($val['norecivedfive']); if(!$norecivedfive) $norecivedfive= NULL;
  $norecivedsix=trim($val['norecivedsix']); if(!$norecivedsix) $norecivedsix= NULL;
  $norecivedseven=trim($val['norecivedseven']); if(!$norecivedseven) $norecivedseven= NULL;
  $norecivedeight=trim($val['norecivedeight']); if(!$norecivedeight) $norecivedeight= NULL;
  $norecivednine=trim($val['norecivednine']); if(!$norecivednine) $norecivednine= NULL;
  $norecivedten=trim($val['norecivedten']); if(!$norecivedten) $norecivedten= NULL;

  
  $recivedeleven=trim($val['recivedeleven']); if(!$recivedeleven) $recivedeleven= NULL;
  $recivedtweleve=trim($val['recivedtweleve']); if(!$recivedtweleve) $recivedtweleve= NULL;
 // print  $val['recivedeleven'].'|||'.$val['recivedtweleve'];
 // exit;

  $noinvstone=trim($val['noinvstone']);  if(!$noinvstone) $noinvstone= NULL;         
  $noinvsttwo=trim($val['noinvsttwo']); if(!$noinvsttwo) $noinvsttwo= NULL;
  $noinvstthree=trim($val['noinvstthree']); if(!$noinvstthree) $noinvstthree= NULL;
  $noinvstfour=trim($val['noinvstfour']); if(!$noinvstfour) $noinvstfour= NULL;
  $noinvstfive=trim($val['noinvstfive']); if(!$noinvstfive) $noinvstfive= NULL;
  $noinvstsix=trim($val['noinvstsix']); if(!$noinvstsix) $noinvstsix= NULL;
  $noinvstseven=trim($val['noinvstseven']); if(!$noinvstseven) $noinvstseven= NULL;
  $noinvsteight=trim($val['noinvsteight']); if(!$noinvsteight) $noinvsteight= NULL;
  $noinvstnine=trim($val['noinvstnine']); if(!$noinvstnine) $noinvstnine= NULL;
  $noinvstten=trim($val['noinvstten']); if(!$noinvstten) $noinvstten= NULL;
  $noinvsteleven=trim($val['noinvsteleven']); if(!$noinvsteleven) $noinvsteleven= NULL;
  $noinvsttweleve=trim($val['noinvsttweleve']); if(!$noinvsttweleve) $noinvsttweleve= NULL;


  $nosetone=trim($val['nosetone']);  if(!$nosetone) $nosetone= NULL;         
  $nosettwo=trim($val['nosettwo']); if(!$nosettwo) $nosettwo= NULL;
  $nosetthree=trim($val['nosetthree']); if(!$nosetthree) $nosetthree= NULL;
  $nosetfour=trim($val['nosetfour']); if(!$nosetfour) $nosetfour= NULL;
  $nosetfive=trim($val['nosetfive']); if(!$nosetfive) $nosetfive= NULL;
  $nosetsix=trim($val['nosetsix']); if(!$nosetsix) $nosetsix= NULL;
  $nosetseven=trim($val['nosetseven']); if(!$nosetseven) $nosetseven= NULL;
  $noseteight=trim($val['noseteight']); if(!$noseteight) $noseteight= NULL;
  $nosetnine=trim($val['nosetnine']); if(!$nosetnine) $nosetnine= NULL;
  $nosetten=trim($val['nosetten']); if(!$nosetten) $nosetten= NULL;
  $noseteleven=trim($val['noseteleven']); if(!$noseteleven) $noseteleven= NULL;
  $nosettweleve=trim($val['nosettweleve']); if(!$nosettweleve) $nosettweleve= NULL;



  $vioobsone=trim($val['vioobsone']);  if(!$vioobsone) $vioobsone= NULL;         
  $vioobstwo=trim($val['vioobstwo']); if(!$vioobstwo) $vioobstwo= NULL;
  $vioobsthree=trim($val['vioobsthree']); if(!$vioobsthree) $vioobsthree= NULL;
  $vioobsfour=trim($val['vioobsfour']); if(!$vioobsfour) $vioobsfour= NULL;
  $vioobsfive=trim($val['vioobsfive']); if(!$vioobsfive) $vioobsfive= NULL;
  $vioobssix=trim($val['vioobssix']); if(!$vioobssix) $vioobssix= NULL;
  $vioobsseven=trim($val['vioobsseven']); if(!$vioobsseven) $vioobsseven= NULL;
  $vioobseight=trim($val['vioobseight']); if(!$vioobseight) $vioobseight= NULL;
  $vioobsnine=trim($val['vioobsnine']); if(!$vioobsnine) $vioobsnine= NULL;
  $vioobsten=trim($val['vioobsten']); if(!$vioobsten) $vioobsten= NULL;
  $vioobseleven=trim($val['vioobseleven']); if(!$vioobseleven) $vioobseleven= NULL;
  $vioobstweleve=trim($val['vioobstweleve']); if(!$vioobstweleve) $vioobstweleve= NULL;


  $remarksone=trim($val['remarksone']);  if(!$remarksone) $remarksone= NULL;         
  $remarkstwo=trim($val['remarkstwo']); if(!$remarkstwo) $remarkstwo= NULL;
  $vioobsthree=trim($val['remarksthree']); if(!$vioobsthree) $vioobsthree= NULL;
 
  $remarksfour=trim($val['remarksfour']); if(!$remarksfour) $remarksfour= NULL;
  $remarksfive=trim($val['remarksfive']); if(!$remarksfive) $remarksfive= NULL;
  $remarkssix=trim($val['remarkssix']); if(!$remarkssix) $remarkssix= NULL;
  $remarksseven=trim($val['remarksseven']); if(!$remarksseven) $remarksseven= NULL;
  $remarkseight=trim($val['remarkseight']); if(!$remarkseight) $remarkseight= NULL;
  $remarksnine=trim($val['remarksnine']); if(!$remarksnine) $remarksnine= NULL;
  $remarksten=trim($val['remarksten']); if(!$remarksten) $remarksten= NULL;
  $remarkseleven=trim($val['remarkseleven']); if(!$remarkseleven) $remarkseleven= NULL;
   $remarkstweleve=trim($val['remarkstweleve']); if(!$remarkstweleve) $remarkstweleve= NULL;








  

  $txn = db_transaction();
    try {

                $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_t8 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
        
           $query_update_A = db_update('labour_factory_statcell_form_5_t8');
        $query_update_A->fields(array(
      'monthly_form_id' => $monthly_form_id, 'compl_reg_no_rec_fa'=> $norecivedone , 'compl_reg_no_rec_pwa' =>$norecivedtwo,  'compl_reg_no_rec_mba' =>$norecivedthree,'compl_reg_no_rec_msihcr' =>$norecivedfour, 'compl_reg_no_rec_car' => $norecivedfive, 'compl_reg_no_rec_clpra' => $norecivedsix, 'compl_unreg_no_rec_fa' => $norecivedseven, 'compl_unreg_no_rec_pwa' => $norecivedeight, 'compl_unreg_no_rec_mba' => $norecivednine, 'compl_unreg_no_rec_msihcr'=> $norecivedten,'compl_unreg_no_rec_car' => $recivedeleven , 'compl_unreg_no_rec_clpra' => $recivedtweleve


       , 'compl_reg_no_inv_fa' => $noinvstone, 'compl_reg_no_inv_pwa' => $noinvsttwo, 'compl_reg_no_inv_mba' => $noinvstthree, 'compl_reg_no_inv_msihcr' => $noinvstfour
        , 'compl_reg_no_inv_car' => $noinvstfive, 'compl_reg_no_inv_clpra' => $noinvstsix, 'compl_unreg_no_inv_fa' => $noinvstseven, 'compl_unreg_no_inv_pwa' => $noinvsteight, 'compl_unreg_no_inv_mba' => $noinvstnine, 'compl_unreg_no_inv_msihcr' => $noinvstten, 'compl_unreg_no_inv_car' => $noinvsteleven, 'compl_unreg_no_inv_clpra' => $noinvsttweleve



         , 'compl_reg_no_settled_fa' => $nosetone, 'compl_reg_no_settled_pwa' => $nosettwo, 'compl_reg_no_settled_mba' => $nosetthree, 'compl_reg_no_settled_msihcr' => $nosetfour
        , 'compl_reg_no_settled_car' => $nosetfive, 'compl_reg_no_settled_clpra' => $nosetsix, 'compl_unreg_no_settled_fa' => $nosetseven, 'compl_unreg_no_settled_pwa' => $noseteight, 'compl_unreg_no_settled_mba' => $nosetnine, 'compl_unreg_no_settled_msihcr' => $nosetten, 'compl_unreg_no_settled_car' => $noseteleven, 'compl_unreg_no_settled_clpra' => $nosettweleve

         ,'compl_reg_violation_fa' => $vioobsone, 'compl_reg_violation_pwa' => $vioobstwo, 'compl_reg_violation_mba' => $vioobsthree, 'compl_reg_violation_msihcr' => $vioobsfour
        , 'compl_reg_violation_car' => $vioobsfive, 'compl_reg_violation_clpra' => $vioobssix, 'compl_unreg_violation_fa' => $vioobsseven, 'compl_unreg_violation_pwa' => $vioobseight, 'compl_unreg_violation_mba' => $vioobsnine, 'compl_unreg_violation_msihcr' => $vioobsten, 'compl_unreg_violation_car' => $vioobseleven, 'compl_unreg_violation_clpra' => $vioobstweleve

         ,'compl_reg_remarks_fa' => $remarksone, 'compl_reg_remarks_pwa' => $remarkstwo, 'compl_reg_remarks_mba' => $vioobsthree, 'compl_reg_remarks_msihcr' => $remarksfour
        , 'compl_reg_remarks_car' => $remarksfive, 'compl_reg_remarks_clpra' => $remarkssix, 'compl_unreg_remarks_fa' => $remarksseven, 'compl_unreg_remarks_pwa' => $remarkseight, 'compl_unreg_remarks_mba' => $remarksnine, 'compl_unreg_remarks_msihcr' => $remarksten, 'compl_unreg_remarks_car' => $remarkseleven, 'compl_unreg_remarks_clpra' => $remarkstweleve




   ));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute(); 

          }
          else
          {
  
          $maxresult=db_query('select  max(complaint_id) maxsl from labour_factory_statcell_form_5_t8'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('complaint_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'compl_reg_no_rec_fa'=> $norecivedone , 'compl_reg_no_rec_pwa' =>$norecivedtwo,  'compl_reg_no_rec_mba' =>$norecivedthree,'compl_reg_no_rec_msihcr' =>$norecivedfour, 'compl_reg_no_rec_car' => $norecivedfive, 'compl_reg_no_rec_clpra' => $norecivedsix, 'compl_unreg_no_rec_fa' => $norecivedseven, 'compl_unreg_no_rec_pwa' => $norecivedeight, 'compl_unreg_no_rec_mba' => $norecivednine, 'compl_unreg_no_rec_msihcr'=> $norecivedten,'compl_unreg_no_rec_car' => $recivedeleven
       , 'compl_unreg_no_rec_clpra' => $recivedtweleve


       , 'compl_reg_no_inv_fa' => $noinvstone, 'compl_reg_no_inv_pwa' => $noinvsttwo, 'compl_reg_no_inv_mba' => $noinvstthree, 'compl_reg_no_inv_msihcr' => $noinvstfour
        , 'compl_reg_no_inv_car' => $noinvstfive, 'compl_reg_no_inv_clpra' => $noinvstsix, 'compl_unreg_no_inv_fa' => $noinvstseven, 'compl_unreg_no_inv_pwa' => $noinvsteight, 'compl_unreg_no_inv_mba' => $noinvstnine, 'compl_unreg_no_inv_msihcr' => $noinvstten, 'compl_unreg_no_inv_car' => $noinvsteleven, 'compl_unreg_no_inv_clpra' => $noinvsttweleve



         , 'compl_reg_no_settled_fa' => $nosetone, 'compl_reg_no_settled_pwa' => $nosettwo, 'compl_reg_no_settled_mba' => $nosetthree, 'compl_reg_no_settled_msihcr' => $nosetfour
        , 'compl_reg_no_settled_car' => $nosetfive, 'compl_reg_no_settled_clpra' => $nosetsix, 'compl_unreg_no_settled_fa' => $nosetseven, 'compl_unreg_no_settled_pwa' => $noseteight, 'compl_unreg_no_settled_mba' => $nosetnine, 'compl_unreg_no_settled_msihcr' => $nosetten, 'compl_unreg_no_settled_car' => $noseteleven, 'compl_unreg_no_settled_clpra' => $nosettweleve

         ,'compl_reg_violation_fa' => $vioobsone, 'compl_reg_violation_pwa' => $vioobstwo, 'compl_reg_violation_mba' => $vioobsthree, 'compl_reg_violation_msihcr' => $vioobsfour
        , 'compl_reg_violation_car' => $vioobsfive, 'compl_reg_violation_clpra' => $vioobssix, 'compl_unreg_violation_fa' => $vioobsseven, 'compl_unreg_violation_pwa' => $vioobseight, 'compl_unreg_violation_mba' => $vioobsnine, 'compl_unreg_violation_msihcr' => $vioobsten, 'compl_unreg_violation_car' => $vioobseleven, 'compl_unreg_violation_clpra' => $vioobstweleve

         ,'compl_reg_remarks_fa' => $remarksone, 'compl_reg_remarks_pwa' => $remarkstwo, 'compl_reg_remarks_mba' => $vioobsthree, 'compl_reg_remarks_msihcr' => $remarksfour
        , 'compl_reg_remarks_car' => $remarksfive, 'compl_reg_remarks_clpra' => $remarkssix, 'compl_unreg_remarks_fa' => $remarksseven, 'compl_unreg_remarks_pwa' => $remarkseight, 'compl_unreg_remarks_mba' => $remarksnine, 'compl_unreg_remarks_msihcr' => $remarksten, 'compl_unreg_remarks_car' => $remarkseleven, 'compl_unreg_remarks_clpra' => $remarkstweleve
        );



       

             db_insert('labour_factory_statcell_form_5_t8')->fields($fieldsA)->execute(); 


  }

   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step8/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step8/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }

           ?>