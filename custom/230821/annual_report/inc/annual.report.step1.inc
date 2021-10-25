<?php

function annual_report_step1( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	 //print $id;
	 $form['step1field'] = array(
          '#title' => t('<font color="DarkGreen"><b> Inspection (A).  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		

														
		
       
	
	  
		 
	 
	
	      
	
	
	
		
	

		
     $form['step1field']['one'] = array
              (
		       '#prefix' => '<table border="1"><tr><td rowspan="4" >', 
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

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1field']['Gftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['Gfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['Gffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['Gffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Gfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Gfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['Gfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
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
	   
	   
           );

                $form['step1field']['Hftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['Hfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['Hffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['Hffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Hfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Hfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['Hfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
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
	   
	   
           );

                $form['step1field']['MAHftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['MAHfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['MAHffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['MAHffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['MAHfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['MAHfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['MAHfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
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
		       '#prefix' => '<table border="1"><tr><td rowspan="4" >', 
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
	   
	   
           );

                $form['step1Bfield']['GftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['GfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['GffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['GffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['GfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['GfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['GfeightddB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
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
	   
	   
           );

                $form['step1Bfield']['HftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['HfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['HffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['HffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['HfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['HfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['HfeightB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
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
	   
	   
           );

                $form['step1Bfield']['MAHftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['MAHfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['MAHffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['MAHffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['MAHfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['MAHfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['MAHfeightB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
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
		       '#prefix' => '<table border="1"><tr><td rowspan="2" >', 
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
		   '#value' => array('0'=>t('select  '),'1'=>t('1'),'2'=>t('2'))
		
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
	   
	   
           ); 

               $form['step1Cfield']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Cfield']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 



                $form['step1Cfield']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
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
        'callback' => 'add_emp_man_det',
        'wrapper' => 'profile_add',
        'method' => 'html',
        'effect' => 'fade'
    )
        );
	
	  
		 
	 
	
	      
	
	
	// Part 4
		
	      $form['step1Dfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  D.No. of Visits paid.  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step1Dfield']['colD1'] = array
              (
		       '#prefix' => '<table border="1"><tr><td colspan="5" >', 
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
	   
	   
           ); 

      $form['step1Dfield']['pwdval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 


              $form['step1Dfield']['mbaval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['carval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['cival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['drival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['balhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['oshhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );
              $form['step1Dfield']['faopval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['frolval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
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
	   
	   
           );


 $form['step1Dfield']['colD13val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD14val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD15val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD16val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

         $form['step1Dfield']['colD17val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td></tr> </table>',
	   
	   
           );


			$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }






