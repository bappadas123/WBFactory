<?php

function annual_report_step7( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	 $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	 
	
	
	    $step7_a_query = db_select('labour_factory_statcell_annual_report_t7_a', 'a');
       
        $step7_a_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step7_a_query->fields('a',array( 's_6' ,'r_3' ,'s_13' ,'s_14' ,'s_16' , 's_17' , 's_18' ,'s_19' ,
  's_21' ,
  's_22' ,
  's_23' ,
  's_24' ,
  's_28' ,
  's_29' ,
  's_30' ,
  's_31' ,
  's_32' ,
  's_33' ,
  's_34' ,
  's_35' ,
  's_36' ,
  's_37' ,
  's_38' ,
  's_42 ',
  'r_65' ,
  'r_66',
  's_46' ,
  's_47' ,
  's_48' ,
  's_51' ,
  's_52' ,
  's_54' ,
  's_55' ,
  's_56' ,
  's_57' ,
  's_58' ,
  's_59' ,
  's_60' ,
  's_61' ,
  's_62',
  's_64' ,
  's_66' ,
  's_67_to_s_73' ,
  's_79' ,
  'r_88' ,
  'r_89' ,
  's_80' ));
        $step7_a_query_result = $step7_a_query->execute(); 
		
		$result_step7=$step7_a_query_result->fetchAssoc();
		$s_6=$result_step7['s_6'];
        $r_3=$result_step7['r_3'];
        $s_13=$result_step7['s_13'];
        $s_14=$result_step7['s_14'];
		$s_16=$result_step7['s_16'];
		$s_17=$result_step7['s_17'];
        $s_18=$result_step7['s_18'];
        $s_19=$result_step7['s_19'];
		
		
		$s_21=$result_step7['s_21'];
		$s_22=$result_step7['s_22'];
		$s_23=$result_step7['s_23'];
		$s_24=$result_step7['s_24'];
		$s_28=$result_step7['s_28'];
		$s_29=$result_step7['s_29'];
		$s_30=$result_step7['s_30'];

		$s_31=$result_step7['s_31'];
		$s_32=$result_step7['s_32'];
		$s_33=$result_step7['s_33'];
		$s_34=$result_step7['s_34'];



		$s_35=$result_step7['s_35'];
		$s_36=$result_step7['s_36'];
		$s_37=$result_step7['s_37'];
		$s_38=$result_step7['s_38'];


		$s_42=$result_step7['s_42'];
		$r_65=$result_step7['r_65'];
		$r_66=$result_step7['r_66'];
		$s_46=$result_step7['s_46'];


		$s_47=$result_step7['s_47'];
		$s_48=$result_step7['s_48'];
		$s_51=$result_step7['s_51'];
		$s_52=$result_step7['s_52'];


		$s_54=$result_step7['s_54'];
		$s_55=$result_step7['s_55'];
		$s_56=$result_step7['s_56'];
		$s_57=$result_step7['s_57'];

		$s_58=$result_step7['s_58'];
		$s_59=$result_step7['s_59'];
		$s_60=$result_step7['s_60'];
		$s_61=$result_step7['s_61'];

		$s_62=$result_step7['s_62'];
		$s_64=$result_step7['s_64'];
		$s_66=$result_step7['s_66'];
		$s_67_to_s_73=$result_step7['s_67_to_s_73'];

		$s_79=$result_step7['s_79'];
		$r_88=$result_step7['r_88'];
		$r_89=$result_step7['r_89'];
		$s_80=$result_step7['s_80'];




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
	
	
	// Part A
		
	      $form['step7Afield'] = array(
          '#title' => t('<b>  Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'  </b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

       $form['step7Afield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

		
     	
$form['step7Afield']['colA1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>7. No. of Factories where violations were observed in respect of</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive">
			   <thead><tr><th >', 
		       '#markup'=>'<b> Regn. Licence etc  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA2'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Plan  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Ventilation & temperature  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Dust & Fume </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Ovr Cowding </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Lighting </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA7'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Drinking Water </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA8'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Latrine & Urinal </b>',
           

		        '#suffix'=>'</th></tr>',
	   
	   
           ); 

        $form['step7Afield']['colA1a'] = array
              (
		       '#prefix' => '<tr><td>', 
		       '#markup'=>'<b> S/6  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA2a'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> R/3  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA3a'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> S/13 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA4a'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> S/14 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA5a'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> S/16 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA6a'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> S/17 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA7a'] = array
              (
		       '#prefix' => '  <td>', 
		        '#markup'=>'<b> S/18 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA8a'] = array
              (
		       '#prefix' => '  <td>', 
		        '#markup'=>'<b> S/19 </b>',
           

		        '#suffix'=>'</td></tr></thead>',
	   
	   
           ); 
         

               $form['step7Afield']['colA1val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_6
	   
	   
           );

                $form['step7Afield']['colA2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$r_3
	   
	   
           );

                $form['step7Afield']['colA3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_13
	   
	   
           );
               $form['step7Afield']['colA4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_14
	   
	   
           );

          $form['step7Afield']['colA5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$s_16
	   
	   
           );
               $form['step7Afield']['colA6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_17
	   
	   
           );
               $form['step7Afield']['colA7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_18
	   
	   
           );
               $form['step7Afield']['colA8val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
		            '#default_value' =>$s_19
	   
	   
           );
               








              $form['step7Afield']['colA9'] = array
              (
		       '#prefix' => '<thead><tr><th>', 
		       '#markup'=>'<b> Fencing of machinery  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA10'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Work on machinery in motion  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA11'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Employment of young persons on dangerous machine  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA12'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Striking gear etc. </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA13'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Hoists & lifts </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA14'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Lifting machinery </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA15'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Revolving machinery </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA16'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Pressure plant </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

              $form['step7Afield']['colA9a'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#markup'=>'<b> S/21  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA10a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/22  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA11a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/23  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA12a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/24. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA13a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/28 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA14a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/29 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA15a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/30 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA16a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/31 </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

               $form['step7Afield']['colA9val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_21
	   
	   
           );

                $form['step7Afield']['colA10val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_22
	   
	   
           );

                $form['step7Afield']['colA11val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_23
	   
	   
           );
               $form['step7Afield']['colA12val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		             '#default_value' =>$s_24
	   
	   
           );

          $form['step7Afield']['colA13val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_28
	   
	   
           );
               $form['step7Afield']['colA14val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_29
	   
	   
           );
               $form['step7Afield']['colA15val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_30
	   
	   
           );
               $form['step7Afield']['colA16val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		       '#suffix'=>'</td></tr>',
		       '#default_value' =>$s_31
	   
	   
           );
              
              
      
             $form['step7Afield']['colA17'] = array
              (
		       '#prefix' => '<thead><tr><th >', 
		       '#markup'=>'<b> Floors stairs, etc.  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA18'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Pits sumps, etc.  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA19'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> excessive wt.  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA20'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Protection of eyes. </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA21'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Dangerous fumes </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA22'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Explosive of inflammable dust etc </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA23'] = array
              (
		       '#prefix' => '  <th >', 
		        '#markup'=>'<b> Precaution in case of fire </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA24'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Washing facilities </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

           $form['step7Afield']['colA17a'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#markup'=>'<b> S/32.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA18a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/33  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA19a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/34.  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA20a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/35. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA21a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/36 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA22a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/37 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA23a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/38 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA24a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/42 </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


            $form['step7Afield']['colA17val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_32
	   
	   
           );

                $form['step7Afield']['colA18val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_33
	   
	   
           );

                $form['step7Afield']['colA19val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_34
	   
	   
           );
               $form['step7Afield']['colA20val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		       '#default_value' =>$s_35
	   
	   
           );

          $form['step7Afield']['colA21val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_36
	   
	   
           );
               $form['step7Afield']['colA22val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_37
	   
	   
           );
               $form['step7Afield']['colA23val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_38
	   
	   
           );
               $form['step7Afield']['colA24val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
		       '#default_value' =>$s_42
	   
	   
           );

              

               $form['step7Afield']['colA25'] = array
              (
		       '#prefix' => '<thead><tr><th>', 
		       '#markup'=>'<b> First aid  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA26'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Ambulance room  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA27'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Canteen.  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA28'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sheer, rest room Lunch room. </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA29'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Creche </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA30'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Weekly hours </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA31'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Weekly holidays </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA32'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Daily hours </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

           $form['step7Afield']['colA25a'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#markup'=>'<b> R/65.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA26a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> R/66  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA27a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/46.  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA28a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/47. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA29a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/48 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA30a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/51 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA31a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/52 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA32a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/54 </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


            $form['step7Afield']['colA25val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$r_65
	   
	   
           );

                $form['step7Afield']['colA26val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$r_66
	   
	   
           );

                $form['step7Afield']['colA27val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_46
	   
	   
           );
               $form['step7Afield']['colA28val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_47
	   
	   
           );

          $form['step7Afield']['colA29val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_48
	   
	   
           );
               $form['step7Afield']['colA30val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_51
	   
	   
           );
               $form['step7Afield']['colA31val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_52
	   
	   
           );
               $form['step7Afield']['colA32val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
		        '#default_value' =>$s_54
	   
	   
           );

              
              $form['step7Afield']['colA33'] = array
              (
		       '#prefix' => '<thead><tr><th>', 
		       '#markup'=>'<b> Rest interval  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA34'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Spread over  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA35'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Night Shifts.  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA36'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Overlapping Shifts. </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA37'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Overtime wages </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA38'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Double Employment </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA39'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Notice of periods of work </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA40'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Register of adult workers </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

           $form['step7Afield']['colA33a'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#markup'=>'<b> S/55.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA34a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/56  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA35a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/57.  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA36a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/58. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA37a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/59 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA38a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/60 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA39a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/61 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA40a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/62 </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


            $form['step7Afield']['colA33val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',

		         '#default_value' =>$s_55
	   
	   
           );

                $form['step7Afield']['colA34val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_56
	   
	   
           );

                $form['step7Afield']['colA35val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_57
	   
	   
           );
               $form['step7Afield']['colA36val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_58
	   
	   
           );

          $form['step7Afield']['colA37val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_59
	   
	   
           );
               $form['step7Afield']['colA38val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		                '#default_value' =>$s_60
	   
	   
           );
               $form['step7Afield']['colA39val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_61
	   
	   
           );
               $form['step7Afield']['colA40val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
		        '#default_value' =>$s_62
	   
	   
           );

             
             
              $form['step7Afield']['colA41'] = array
              (
		       '#prefix' => '<thead><tr><th>', 
		       '#markup'=>'<b> Exemption Rules  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Afield']['colA42'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Employment of Women  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA43'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Employment of Young persons.  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Afield']['colA44'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Leave with wage. </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Afield']['colA45'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Leave register </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA46'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Leave book </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Afield']['colA47'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Wages for Leave periods </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step7Afield']['colA48'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

           $form['step7Afield']['colA41a'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#markup'=>'<b> S/64.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step7Afield']['colA42a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/66  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA43a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> S/67 to S/73  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step7Afield']['colA44a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> S/79. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step7Afield']['colA45a'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> R/88 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA46a'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> R/89 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step7Afield']['colA47a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> S/80 </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step7Afield']['colA48a'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b>  </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


            $form['step7Afield']['colA41val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_64
	   
	   
           );

                $form['step7Afield']['colA42val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_66
	   
	   
           );

                $form['step7Afield']['colA43val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_67_to_s_73
	   
	   
           );
               $form['step7Afield']['colA44val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		              '#default_value' =>$s_79
	   
	   
           );

          $form['step7Afield']['colA45val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$r_88
	   
	   
           );
               $form['step7Afield']['colA46val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$r_89
	   
	   
           );
               $form['step7Afield']['colA47val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_80
	   
	   
           );
               $form['step7Afield']['colA48val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'&nbsp',

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           );

              $form['step7Afield']['submit_button_7A']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save  '),
																
																'#submit' => array('step7_parta_save'),
																 
																);

  // PART B
              
   
        
          
        $step47_select_query = db_select('labour_factory_statcell_annual_report_t7_rule_47', 'b');
       
        $step47_select_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
        $step47_select_query->fields('b',array('s_i','s_ii','s_iii','s_iv','s_v','s_vi','s_vii'));
        $step47_select_query_result = $step47_select_query->execute(); 
		
		$result_step7b=$step47_select_query_result->fetchAssoc();
		$s_i=$result_step7b['s_i'];
        $s_ii=$result_step7b['s_ii'];
        $s_iii=$result_step7b['s_iii'];
        $s_iv=$result_step7b['s_iv'];
		
		$s_v=$result_step7b['s_v'];
		$s_vi=$result_step7b['s_vi'];
		$s_vii=$result_step7b['s_vii'];
	

        
   
		
	      $form['step7Bfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step7Bfield']['colB1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>RULE 47</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive">
			   <thead>
			   <tr><th>', 
		       '#markup'=>'<b> Sch. I  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Bfield']['colB2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. II  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Bfield']['colB3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. III  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Bfield']['colB4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. IV </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Bfield']['colB5'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. V </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Bfield']['colB6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. VI </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Bfield']['colB7'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. VII </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 


              
       
       

                $form['step7Bfield']['colB1val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		        '#default_value' =>$s_i
	   
	   
           );
               $form['step7Bfield']['colB2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_ii
	   
	   
           );

          $form['step7Bfield']['colB3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_iii
	   
	   
           );
               $form['step7Bfield']['colB4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$s_iv
	   
	   
           );
               $form['step7Bfield']['colB5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_v
	   
	   
           );
               $form['step7Bfield']['colB6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$s_vi
	   
	   
           );
               $form['step7Bfield']['colB7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table>',
		          '#default_value' =>$s_vii
	   
	   
           );


 $form['step7Bfield']['submit_button_7B']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save Rule 47  '),
																
																'#submit' => array('step7_partb_save'),
																 
																);


       

           // PART C
              
   
        $step94_select_query = db_select('labour_factory_statcell_annual_report_t7_rule_94', 'c');
       
        $step94_select_query->condition('c.annual_inspection_id',trim($filenumber),'=');
      
		
        $step94_select_query->fields('c',array('s_i' ,
  's_ii' ,
  's_iii' ,
  's_iv' ,
  's_v' ,
  's_vi' ,
  's_vii' ,
  's_viii' ,
  's_ix' ,
  's_x' ,
  's_xi' ,
  's_xii' ,
  's_xiii' ,
  's_xiv' ,
  's_xv' ,
  's_xvi' ,
  's_xvii' ,
  's_xviii' ,
  's_xix' ,
  's_xx',
  's_xxi' ,
  's_xxii',
  's_xxiii' ,
  's_xxiv' ,
  's_xxv' ,
  's_xxvi',
  's_xxvii' ,
  's_xxviii' ,
  's_xxix' ,
  's_xxx' ,
  's_xxxi' ,

  's_xxxii' ));
        $step94_select_query_result = $step94_select_query->execute(); 
		
		$result_step94=$step94_select_query_result->fetchAssoc();
		$s_i=$result_step94['s_i'];
        $s_ii=$result_step94['s_ii'];
        $s_iii=$result_step94['s_iii'];
        $s_iv=$result_step94['s_iv'];
		
		$s_v=$result_step94['s_v'];
		$s_vi=$result_step94['s_vi'];
		$s_vii=$result_step94['s_vii'];
		$s_viii=$result_step94['s_viii'];
		$s_ix=$result_step94['s_ix'];
		$s_x=$result_step94['s_x'];


		$s_xi=$result_step94['s_xi'];
		$s_xii=$result_step94['s_xii'];
		$s_xiii=$result_step94['s_xiii'];
		$s_xiv=$result_step94['s_xiv'];
		$s_xv=$result_step94['s_xv'];
		$s_xvi=$result_step94['s_xvi'];
		$s_xvii=$result_step94['s_xvii'];
		$s_xviii=$result_step94['s_xviii'];
		$s_xix=$result_step94['s_xix'];
		$s_xx=$result_step94['s_xx'];


		$s_xxi=$result_step94['s_xxi'];
		$s_xxii=$result_step94['s_xxii'];
		$s_xxiii=$result_step94['s_xxiii'];
		$s_xxiv=$result_step94['s_xxiv'];
		$s_xxv=$result_step94['s_xxv'];
		$s_xxvi=$result_step94['s_xxvi'];
		$s_xxvii=$result_step94['s_xxvii'];
		$s_xxviii=$result_step94['s_xxviii'];
		$s_xxix=$result_step94['s_xxix'];
		$s_xxx=$result_step94['s_xxx'];

		$s_xxxi=$result_step94['s_xxxi'];
		$s_xxxii=$result_step94['s_xxxii'];



   
		
	      $form['step7Cfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step7Cfield']['colC1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>RULE 94</b></div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th>', 
		       '#markup'=>'<b> Sch. I  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Cfield']['colC2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. II  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. III  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. IV </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Cfield']['colC5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. V </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. VI </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC7'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. VII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

            $form['step7Cfield']['colC8'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. VIII  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC9'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. IX  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC10'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. X </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Cfield']['colC11'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XI </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC12'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. XII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC13'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XIII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC14'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XIV </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC15'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XV </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC16'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XVI </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 


              $form['step7Cfield']['colC1val'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		          '#suffix'=>'</td>',
		           '#default_value' =>$s_i
	   
	   
           );


                $form['step7Cfield']['colC2val'] = array
              (
		       '#prefix' => ' <td   >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_ii
	   
	   
           ); 


               $form['step7Cfield']['colC3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_iii
	   
	   
           ); 


               $form['step7Cfield']['colC4val'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_iv
	   
	   
           ); 

               $form['step7Cfield']['colC5val'] = array
              (
		       '#prefix' => ' <td   >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_v
	   
	   
           ); 

              $form['step7Cfield']['colC6val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_vi
	   
	   
           ); 

              $form['step7Cfield']['colC7val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_vii
	   
	   
           ); 

            $form['step7Cfield']['colC8val'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_viii
	   
	   
           ); 


               $form['step7Cfield']['colC9val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_ix
	   
	   
           ); 


               $form['step7Cfield']['colC10val'] = array
              (
		       '#prefix' => ' <td   >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_x
	   
	   
           ); 

               $form['step7Cfield']['colC11val'] = array
              (
		       '#prefix' => ' <td   >', 
		     '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xi
	   
	   
           ); 

              $form['step7Cfield']['colC12val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xii
	   
	   
           ); 

              $form['step7Cfield']['colC13val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xiii
	   
	   
           ); 
            $form['step7Cfield']['colC14val'] = array
              (
		       '#prefix' => '  <td  >', 
		     '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xiv
	   
	   
           ); 
            $form['step7Cfield']['colC15val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xv
	   
	   
           ); 
            $form['step7Cfield']['colC16val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td></tr>',
		           '#default_value' =>$s_xvi
	   
	   
           ); 

       

            $form['step7Cfield']['colC17'] = array
              (
		       '#prefix' => '<thead><th>', 
		       '#markup'=>'<b> Sch. XVII  </b>',

		          '#suffix'=>'</th>',
		            
	   
	   
           );


                $form['step7Cfield']['colC18'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. XVIII  </b>',
           

		        '#suffix'=>'</th>',
		           
	   
	   
           ); 


               $form['step7Cfield']['colC19'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XIX  </b>',
           

		        '#suffix'=>'</th>',
		         
	   
	   
           ); 


               $form['step7Cfield']['colC20'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XX </b>',
           

		        '#suffix'=>'</th>',
		          
	   
	   
           ); 

               $form['step7Cfield']['colC21'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XXI </b>',
           

		        '#suffix'=>'</th>',
		         
	   
	   
           ); 

              $form['step7Cfield']['colC22'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XXIII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC23'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XXIII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

            $form['step7Cfield']['colC24'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. XXIV  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC25'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XXV  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Cfield']['colC26'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> Sch. XXVI </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Cfield']['colC27'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XXVII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC28'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Sch. XXVIII </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Cfield']['colC29'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XXIX </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC30'] = array
              (
		       '#prefix' => '  <th >', 
		        '#markup'=>'<b> Sch. XXX </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC31'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XXXI </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
            $form['step7Cfield']['colC32'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sch. XXXII </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 


              $form['step7Cfield']['colC17val'] = array
              (
		       '#prefix' => '<tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		          '#suffix'=>'</td>',
		             '#default_value' =>$s_xvii
	   
	   
           );


                $form['step7Cfield']['colC18val'] = array
              (
		       '#prefix' => ' <td   >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xviii
	   
	   
           ); 


               $form['step7Cfield']['colC19val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xix
	   
	   
           ); 


               $form['step7Cfield']['colC20val'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xx
	   
	   
           ); 

               $form['step7Cfield']['colC21val'] = array
              (
		       '#prefix' => ' <td   >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxi
	   
	   
           ); 

              $form['step7Cfield']['colC22val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxii
	   
	   
           ); 

              $form['step7Cfield']['colC23val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxiii
	   
	   
           ); 

            $form['step7Cfield']['colC24val'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxiv
	   
	   
           ); 


               $form['step7Cfield']['colC25val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxv
	   
	   
           ); 


               $form['step7Cfield']['colC26val'] = array
              (
		       '#prefix' => ' <td   >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxvi
	   
	   
           ); 

               $form['step7Cfield']['colC27val'] = array
              (
		       '#prefix' => ' <td   >', 
		     '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxvii
	   
	   
           ); 

              $form['step7Cfield']['colC28val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxviii
	   
	   
           ); 

              $form['step7Cfield']['colC29val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxix
	   
	   
           ); 
            $form['step7Cfield']['colC30val'] = array
              (
		       '#prefix' => '  <td  >', 
		     '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxx
	   
	   
           ); 
            $form['step7Cfield']['colC31val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td>',
		           '#default_value' =>$s_xxxi
	   
	   
           ); 
            $form['step7Cfield']['colC32val'] = array
              (
		       '#prefix' => '  <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           

		        '#suffix'=>'</td></tr></table></div>',
		           '#default_value' =>$s_xxxii
	   
	   
           );     

           $form['step7Cfield']['submit_button_7C']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save Rule 94  '),
																
																'#submit' => array('step7_partc_save'),
																 
																);

  // PART D
              
      
         $step7_tabh_query = db_select('labour_factory_statcell_annual_report_t7_tab_h', 'd');
       
        $step7_tabh_query->condition('d.annual_inspection_id',trim($filenumber),'=');
      
		
        $step7_tabh_query->fields('d',array('s_7a','r_63b','r_63c','r_63d','r_63e','r_63f','r_63g','r_63j','r_63k','r_63l'));
        $step7_tabh_query_result = $step7_tabh_query->execute(); 
		
		$result_tabh=$step7_tabh_query_result->fetchAssoc();
		$s_7a=$result_tabh['s_7a'];
        $r_63b=$result_tabh['r_63b'];
        $r_63c=$result_tabh['r_63c'];
        $r_63d=$result_tabh['r_63d'];
		
		$r_63e=$result_tabh['r_63e'];
		$r_63f=$result_tabh['r_63f'];
		$r_63g=$result_tabh['r_63g'];
		$r_63j=$result_tabh['r_63j'];
		$r_63k=$result_tabh['r_63k'];
		$r_63l=$result_tabh['r_63l'];
      
      $form['step7Dfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step7Dfield']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>TAB-H</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th  >', 
		       '#markup'=>'<b> S-7A  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step7Dfield']['colD2'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> R-63B  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Dfield']['colD3'] = array
              (
		       '#prefix' => ' <th >', 
		        '#markup'=>'<b> R-63C  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step7Dfield']['colD4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> R-63D </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step7Dfield']['colD5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> R-63E </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Dfield']['colD6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> R-63F </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step7Dfield']['colD7'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> R-63G </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

    $form['step7Dfield']['colD8'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> R-63J </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

            $form['step7Dfield']['colD9'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> R-63K </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           );
              
 $form['step7Dfield']['colD10'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> R-63L </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           );
       

       

                $form['step7Dfield']['colD1val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$s_7a
	   
	   
           );
               $form['step7Dfield']['colD2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$r_63b
	   
	   
           );

          $form['step7Dfield']['colD3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		             '#default_value' =>$r_63c
	   
	   
           );
               $form['step7Dfield']['colD4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$r_63d

	   
	   
           );
               $form['step7Dfield']['colD5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$r_63e
	   
	   
           );
               $form['step7Dfield']['colD6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$r_63f
	   
	   
           );
               $form['step7Dfield']['colD7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$r_63g
	   
	   
           );

            $form['step7Dfield']['colD8val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$r_63j
	   
	   
           );
            $form['step7Dfield']['colD9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$r_63k
	   
	   
           );
            $form['step7Dfield']['colD10val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table></div>',
		           '#default_value' =>$r_63l
	   
	   
           );

    

   
             
            
      
              


			$form['step7Dfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save TAB-H '),
																'#submit' => array('step7_partd_save'),
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }

/*
function annual_report_step7_submit($form , $form_state) {	

                


 }

*/






function step7_parta_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);

    $colA1val=trim($val['colA1val']); if(!$colA1val)  $colA1val= NULL; 
$colA2val=trim($val['colA2val']); if(!$colA2val)  $colA2val= NULL; 
$colA3val=trim($val['colA3val']); if(!$colA3val)  $colA3val= NULL;  
$colA4val=trim($val['colA4val']); if(!$colA4val)  $colA4val= NULL; 
$colA5val=trim($val['colA5val']); if(!$colA5val)  $colA5val= NULL;  
$colA6val=trim($val['colA6val']); if(!$colA6val)  $colA6val= NULL; 

$colA7val=trim($val['colA7val']); if(!$colA7val)  $colA7val= NULL;   
$colA8val=trim($val['colA8val']); if(!$colA8val)  $colA8val= NULL;   
$colA9val=trim($val['colA9val']); if(!$colA9val)  $colA9val= NULL; 
$colA10val=trim($val['colA10val']); if(!$colA10val)  $colA10val= NULL;   
$colA11val=trim($val['colA11val']); if(!$colA11val)  $colA11val= NULL;  


$colA12val=trim($val['colA12val']); if(!$colA12val)  $colA12val= NULL; 
$colA13val=trim($val['colA13val']); if(!$colA13val)  $colA13val= NULL; 
$colA14val=trim($val['colA14val']); if(!$colA14val)  $colA14val= NULL; 
$colA15val=trim($val['colA15val']); if(!$colA15val)  $colA15val= NULL; 
$colA16val=trim($val['colA16val']); if(!$colA16val)  $colA16val= NULL;  



$colA17val=trim($val['colA17val']); if(!$colA17val)  $colA17val= NULL; 
$colA18val=trim($val['colA18val']); if(!$colA18val)  $colA18val= NULL; 
$colA19val=trim($val['colA19val']); if(!$colA19val)  $colA19val= NULL; 
$colA20val=trim($val['colA20val']); if(!$colA20val)  $colA20val= NULL; 
$colA21val=trim($val['colA21val']); if(!$colA21val)  $colA21val= NULL;   




$colA22val=trim($val['colA22val']); if(!$colA22val)  $colA22val= NULL; 
$colA23val=trim($val['colA23val']); if(!$colA23val)  $colA23val= NULL; 
$colA24val=trim($val['colA24val']); if(!$colA24val)  $colA24val= NULL; 
$colA25val=trim($val['colA25val']); if(!$colA25val)  $colA25val= NULL; 
$colA26val=trim($val['colA26val']); if(!$colA26val)  $colA26val= NULL; 


$colA27val=trim($val['colA27val']); if(!$colA27val)  $colA27val= NULL; 
$colA28val=trim($val['colA28val']); if(!$colA28val)  $colA28val= NULL; 
$colA29val=trim($val['colA29val']); if(!$colA29val)  $colA29val= NULL; 
$colA30val=trim($val['colA30val']); if(!$colA30val)  $colA30val= NULL; 
$colA31val=trim($val['colA31val']); if(!$colA31val)  $colA31val= NULL; 




   
$colA32val=trim($val['colA32val']); if(!$colA32val)  $colA32val= NULL;   
$colA33val=trim($val['colA33val']); if(!$colA33val)  $colA33val= NULL;   
$colA34val=trim($val['colA34val']); if(!$colA34val)  $colA34val= NULL;   
$colA35val=trim($val['colA35val']); if(!$colA35val)  $colA35val= NULL;   
$colA36val=trim($val['colA36val']); if(!$colA36val)  $colA36val= NULL;   
$colA37val=trim($val['colA37val']); if(!$colA37val)  $colA37val= NULL;   
$colA38val=trim($val['colA38val']); if(!$colA38val)  $colA38val= NULL;   
$colA39val=trim($val['colA39val']); if(!$colA39val)  $colA39val= NULL;  


$colA40val=trim($val['colA40val']); if(!$colA40val)  $colA40val= NULL;   
$colA41val=trim($val['colA41val']); if(!$colA41val)  $colA41val= NULL;   
$colA42val=trim($val['colA42val']); if(!$colA42val)  $colA42val= NULL;   
$colA43val=trim($val['colA43val']); if(!$colA43val)  $colA43val= NULL;   
$colA44val=trim($val['colA44val']); if(!$colA44val)  $colA44val= NULL;   
$colA45val=trim($val['colA45val']); if(!$colA45val)  $colA45val= NULL;   
$colA46val=trim($val['colA46val']); if(!$colA46val)  $colA46val= NULL;   
$colA47val=trim($val['colA47val']); if(!$colA47val)  $colA47val= NULL; 


 $txn = db_transaction();
	  try {

	   $query_7a=db_query('select  * from labour_factory_statcell_annual_report_t7_a where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));



	     if($query_7a->rowCount() > 0 ) {

	      $query_update_A = db_update('labour_factory_statcell_annual_report_t7_a');

           $query_update_A->fields(array(
		  's_6' =>$colA1val, 'r_3' => $colA2val,  's_13' => $colA3val,'s_14' => $colA4val, 's_16' => $colA5val, 's_17' => $colA6val, 's_18' => $colA7val, 's_19' => $colA8val,

's_21' =>$colA9val, 's_22' => $colA10val,  's_23' => $colA11val,'s_24' => $colA12val, 's_28' => $colA13val, 's_29' => $colA14val, 's_30' => $colA15val, 's_31' => $colA16val,

's_32' =>$colA17val, 's_33' => $colA18val,  's_34' => $colA19val,'s_35' => $colA20val, 's_36' => $colA21val, 's_37' => $colA22val, 's_38' => $colA23val, 's_42' => $colA24val,

'r_65' =>$colA25val, 'r_66' => $colA26val,  's_46' => $colA27val,'s_47' => $colA28val, 's_48' => $colA29val, 's_51' => $colA30val, 's_52' => $colA31val, 's_54' => $colA32val,

's_55' =>$colA33val, 's_56' => $colA34val,  's_57' => $colA35val,'s_58' => $colA36val, 's_59' => $colA37val, 's_60' => $colA38val, 's_61' => $colA39val, 's_62' => $colA40val,

's_64' =>$colA41val, 's_66' => $colA42val,  's_67_to_s_73' => $colA43val,'s_79' => $colA44val, 'r_88' => $colA45val, 'r_89' => $colA46val, 's_80' => $colA47val ));
										
										
										
       $query_update_A->condition('annual_inspection_id',$inspectionid);
       $query_update_A->execute();
   }

        else
	      {
	      	



            $maxresult5=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t7_a');	
	        $result5=$maxresult5->fetchAssoc();
	        $max_sl_number5 = trim($result5['maxsl']); 
            if($max_sl_number5==0){$querystring5=1;	}else{ $querystring5=$max_sl_number5+1; }
		    $autoGENNO5=$querystring5;

 $fieldsA = array('row_id' => $autoGENNO5, 'annual_inspection_id' =>$inspectionid,'s_6' =>$colA1val, 'r_3' => $colA2val,  's_13' => $colA3val,'s_14' => $colA4val, 's_16' => $colA5val, 's_17' => $colA6val, 's_18' => $colA7val, 's_19' => $colA8val,

's_21' =>$colA9val, 's_22' => $colA10val,  's_23' => $colA11val,'s_24' => $colA12val, 's_28' => $colA13val, 's_29' => $colA14val, 's_30' => $colA15val, 's_31' => $colA16val,

's_32' =>$colA17val, 's_33' => $colA18val,  's_34' => $colA19val,'s_35' => $colA20val, 's_36' => $colA21val, 's_37' => $colA22val, 's_38' => $colA23val, 's_42' => $colA24val,

'r_65' =>$colA25val, 'r_66' => $colA26val,  's_46' => $colA27val,'s_47' => $colA28val, 's_48' => $colA29val, 's_51' => $colA30val, 's_52' => $colA31val, 's_54' => $colA32val,

's_55' =>$colA33val, 's_56' => $colA34val,  's_57' => $colA35val,'s_58' => $colA36val, 's_59' => $colA37val, 's_60' => $colA38val, 's_61' => $colA39val, 's_62' => $colA40val,

's_64' =>$colA41val, 's_66' => $colA42val,  's_67_to_s_73' => $colA43val,'s_79' => $colA44val, 'r_88' => $colA45val, 'r_89' => $colA46val, 's_80' => $colA47val



 );
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t7_a')->fields($fieldsA)->execute();


                  }



               $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);
                   // }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);
	             

	              }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	 

     } 

     function step7_partb_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);

    $colB1val=trim($val['colB1val']); if(!$colB1val)  $colB1val= NULL;   
	$colB2val=trim($val['colB2val']); if(!$colB2val)  $colB2val= NULL;   
	$colB3val=trim($val['colB3val']); if(!$colB3val)  $colB3val= NULL;   

	$colB4val=trim($val['colB4val']); if(!$colB4val)  $colB4val= NULL; 
    $colB5val=trim($val['colB5val']); if(!$colB5val)  $colB5val= NULL; 
    $colB6val=trim($val['colB6val']); if(!$colB6val)  $colB6val= NULL; 
    $colB7val=trim($val['colB7val']); if(!$colB7val)  $colB7val= NULL; 

  $txn = db_transaction();
	  try {

      
           $query_rule47=db_query('select  * from labour_factory_statcell_annual_report_t7_rule_47 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


               if( $query_rule47->rowCount() > 0  ) { 

                $query_update_B = db_update('labour_factory_statcell_annual_report_t7_rule_47');
      $query_update_B->fields(array(
		 's_i' =>$colB1val, 's_ii' => $colB2val, 's_iii' => $colB3val, 's_iv' => $colB4val, 's_v' => $colB5val, 's_vi' => $colB6val, 's_vii' => $colB7val ));
		  $query_update_B->condition('annual_inspection_id',$inspectionid);	
		  $query_update_B->execute();


           }


           else
           {

           $maxresult2=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t7_rule_47');	
	        $result2=$maxresult2->fetchAssoc();
	        $max_sl_number2 = trim($result2['maxsl']); 
            if($max_sl_number2==0){$querystring2=1;	}else{ $querystring2=$max_sl_number2+1; }
		    $autoGENNO2=$querystring2;

 $fieldsE = array('row_id' => $autoGENNO2, 'annual_inspection_id' =>$inspectionid,'s_i' =>$colB1val, 's_ii' => $colB2val, 's_iii' => $colB3val, 's_iv' => $colB4val, 's_v' => $colB5val, 's_vi' => $colB6val, 's_vii' => $colB7val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t7_rule_47')->fields($fieldsE)->execute();
           }


      $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);
                   // }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);

	  	}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }

 }

 function step7_partc_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);

    $colC1val=trim($val['colC1val']); if(!$colC1val)  $colC1val= NULL;   
$colC2val=trim($val['colC2val']); if(!$colC2val)  $colC2val= NULL;   
$colC3val=trim($val['colC3val']);  if(!$colC3val)  $colC3val= NULL;

$colC4val=trim($val['colC4val']); if(!$colC4val)  $colC4val= NULL;   
$colC5val=trim($val['colC5val']); if(!$colC5val)  $colC5val= NULL;   
$colC6val=trim($val['colC6val']); if(!$colC6val)  $colC6val= NULL;   
$colC7val=trim($val['colC7val']); if(!$colC7val)  $colC7val= NULL;   
$colC8val=trim($val['colC8val']); if(!$colC8val)  $colC8val= NULL;   
$colC9val=trim($val['colC9val']); if(!$colC9val)  $colC9val= NULL;   
$colC10val=trim($val['colC10val']);if(!$colC10val)  $colC10val= NULL;   

$colC11val=trim($val['colC11val']); if(!$colC11val)  $colC11val= NULL;   
$colC12val=trim($val['colC12val']); if(!$colC12val)  $colC12val= NULL;   
$colC13val=trim($val['colC13val']); if(!$colC13val)  $colC13val= NULL;   
$colC14val=trim($val['colC14val']); if(!$colC14val)  $colC14val= NULL;   
$colC15val=trim($val['colC15val']); if(!$colC15val)  $colC15val= NULL;   
$colC16val=trim($val['colC16val']); if(!$colC16val)  $colC16val= NULL;   
$colC17val=trim($val['colC17val']); if(!$colC17val)  $colC17val= NULL;   
$colC18val=trim($val['colC18val']); if(!$colC18val)  $colC18val= NULL;   
$colC19val=trim($val['colC19val']); if(!$colC19val)  $colC19val= NULL;   
$colC20val=trim($val['colC20val']); if(!$colC20val)  $colC20val= NULL;   

$colC21val=trim($val['colC21val']); if(!$colC21val)  $colC21val= NULL;   
$colC22val=trim($val['colC22val']); if(!$colC22val)  $colC22val= NULL;   
$colC23val=trim($val['colC23val']); if(!$colC23val)  $colC23val= NULL;   
  
$colC24val=trim($val['colC24val']);if(!$colC24val)  $colC24val= NULL;     
$colC25val=trim($val['colC25val']);if(!$colC25val)  $colC25val= NULL;   
$colC26val=trim($val['colC26val']); if(!$colC26val)  $colC26val= NULL; 
$colC27val=trim($val['colC27val']); if(!$colC27val)  $colC27val= NULL;  
$colC28val=trim($val['colC28val']);if(!$colC28val)  $colC28val= NULL; 
$colC29val=trim($val['colC29val']); if(!$colC29val)  $colC29val= NULL;
$colC30val=trim($val['colC30val']); if(!$colC30val)  $colC30val= NULL;

$colC31val=trim($val['colC31val']); if(!$colC31val)  $colC31val= NULL;
$colC32val=trim($val['colC32val']);  if(!$colC32val)  $colC32val= NULL;
  

  $txn = db_transaction();
	  try {

      
         $query_rule94=db_query('select  * from labour_factory_statcell_annual_report_t7_rule_94 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


               if( $query_rule94->rowCount() > 0  ) { 

               $query_update_C = db_update('labour_factory_statcell_annual_report_t7_rule_94');
      $query_update_C->fields(array(
		 's_i' =>$colC1val, 's_ii' => $colC2val, 's_iii' => $colC3val, 's_iv' => $colC4val, 's_v' => $colC5val, 's_vi' => $colC6val, 's_vii' => $colC7val,  's_viii' => $colC8val
, 's_ix' => $colC9val, 's_x' => $colC10val 

, 's_xi' => $colC11val,  's_xii' => $colC12val, 's_xiii' => $colC13val, 's_xiv' => $colC14val, 's_xv' => $colC15val, 's_xvi' => $colC16val, 's_xvii' => $colC17val, 's_xviii' => $colC18val, 's_xix' => $colC19val, 's_xx' => $colC20val


, 's_xxi' => $colC21val,  's_xxii' => $colC22val, 's_xxiii' => $colC23val, 's_xxiv' => $colC24val, 's_xxv' => $colC25val, 's_xxvi' => $colC26val, 's_xxvii' => $colC27val, 's_xxviii' => $colC28val, 's_xxix' => $colC29val, 's_xxx' => $colC30val,



's_xxxi' => $colC31val, 's_xxxii' => $colC32val ));
		  $query_update_C->condition('annual_inspection_id',$inspectionid);	
		  $query_update_C->execute(); 


           }


           else
           {
  
          $maxresult1=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t7_rule_94');	
	        $result1=$maxresult1->fetchAssoc();
	        $max_sl_number1 = trim($result1['maxsl']); 
            if($max_sl_number1==0){$querystring1=1;	}else{ $querystring1=$max_sl_number1+1; }
		    $autoGENNO1=$querystring1;

 $fieldsE = array('row_id' => $autoGENNO1, 'annual_inspection_id' =>$inspectionid,'s_i' =>$colC1val, 's_ii' => $colC2val, 's_iii' => $colC3val, 's_iv' => $colC4val, 's_v' => $colC5val, 's_vi' => $colC6val, 's_vii' => $colC7val,  's_viii' => $colC8val
, 's_ix' => $colC9val, 's_x' => $colC10val 

, 's_xi' => $colC11val,  's_xii' => $colC12val, 's_xiii' => $colC13val, 's_xiv' => $colC14val, 's_xv' => $colC15val, 's_xvi' => $colC16val, 's_xvii' => $colC17val, 's_xviii' => $colC18val, 's_xix' => $colC19val, 's_xx' => $colC20val


, 's_xxi' => $colC21val,  's_xxii' => $colC22val, 's_xxiii' => $colC23val, 's_xxiv' => $colC24val, 's_xxv' => $colC25val, 's_xxvi' => $colC26val, 's_xxvii' => $colC27val, 's_xxviii' => $colC28val, 's_xxix' => $colC29val, 's_xxx' => $colC30val,



's_xxxi' => $colC31val, 's_xxxii' => $colC32val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t7_rule_94')->fields($fieldsE)->execute();
          
           }


      $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);
                   // }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);

	  	}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	  

 }

 function step7_partd_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);

    $colD1val=trim($val['colD1val']); if(!$colD1val)  $colD1val= NULL;   
	$colD2val=trim($val['colD2val']); if(!$colD2val)  $colD2val= NULL;   
	$colD3val=trim($val['colD3val']); if(!$colD3val)  $colD3val= NULL;   

	$colD4val=trim($val['colD4val']); if(!$colD4val)  $colD4val= NULL; 
    $colD5val=trim($val['colD5val']); if(!$colD5val)  $colD5val= NULL; 
    $colD6val=trim($val['colD6val']); if(!$colD6val)  $colD6val= NULL; 
    $colD7val=trim($val['colD7val']); if(!$colD7val)  $colD7val= NULL; 
    $colD8val=trim($val['colD8val']); if(!$colD8val)  $colD8val= NULL; 
    $colD9val=trim($val['colD9val']); if(!$colD9val)  $colD9val= NULL;
    $colD10val=trim($val['colD10val']); if(!$colD10val) $colD10val= NULL; 
  

  $txn = db_transaction();
	  try {

      
           $query_tabh=db_query('select  * from labour_factory_statcell_annual_report_t7_tab_h where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


               if( $query_tabh->rowCount() > 0  ) { 

               $query_update_D = db_update('labour_factory_statcell_annual_report_t7_tab_h');
      $query_update_D->fields(array(
		  's_7a' =>$colD1val, 'r_63b' => $colD2val, 'r_63c' => $colD3val, 'r_63d' => $colD4val, 'r_63e' => $colD5val, 'r_63f' => $colD6val, 'r_63g' => $colD7val, 'r_63j' => $colD8val, 'r_63k' => $colD9val, 'r_63l' => $colD10val ));
										
										
										
       $query_update_D->condition('annual_inspection_id',$inspectionid);
       $query_update_D->execute(); 


           }


           else
           {
  
          $maxresult4=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t7_tab_h');	
	        $result4=$maxresult4->fetchAssoc();
	        $max_sl_number4 = trim($result4['maxsl']); 
            if($max_sl_number4==0){$querystring4=1;	}else{ $querystring4=$max_sl_number4+1; }
		    $autoGENNO4=$querystring4;

 $fieldsE = array('row_id' => $autoGENNO4, 'annual_inspection_id' =>$inspectionid,'s_7a' =>$colD1val, 'r_63b' => $colD2val, 'r_63c' => $colD3val, 'r_63d' => $colD4val, 'r_63e' => $colD5val, 'r_63f' => $colD6val, 'r_63g' => $colD7val, 'r_63j' => $colD8val, 'r_63k' => $colD9val, 'r_63l' => $colD10val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t7_tab_h')->fields($fieldsE)->execute(); 
          
           }


      $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);
                   // }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);

	  	}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step7/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	  

 }