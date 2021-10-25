<?php global $base_root, $base_path, $user; 
if ($user->uid!=0){
	$userData = array();
	$fname = "";
	$role = "";
	if(array_key_exists(4, $user->roles)){
		$userData = get_details_applicant($user->uid);
		if(!empty($userData)){
			if($userData['fullname']!=""){
				$fname = $userData['fullname'];
			}else{
				$fname = $userData['name'];
			}
			$role = 'Applicant';
		}
	}else{
		$userData = get_details_employee($user->uid);
		if(!empty($userData)){
			if($userData['fname']!=""){
				$fname = $userData['fname'];
			}else{
				$fname = $userData['name'];
			} 
			/*if(array_key_exists(5, $user->roles)){
				$role = 'Plan Section';
			}else*/
			if(array_key_exists(7, $user->roles)){
				$role = 'Cms Manager';
			}/*elseif(array_key_exists(8, $user->roles)){
				$role = 'Registration Section';
			}*/elseif(array_key_exists(9, $user->roles)){
				$role = 'Inspector of Factories';
			}elseif(array_key_exists(10, $user->roles)){
				$role = 'Deputy Chief Inspector of Factories';
			}elseif(array_key_exists(11, $user->roles)){
				$role = 'Joint Chief Inspector of Factories';
			}/*elseif(array_key_exists(12, $user->roles)){
				$role = 'Chief Inspector';
			}*/elseif(array_key_exists(13, $user->roles)){
				$role = 'Deputy Chief Inspector of Factories (Chemical)';
			}elseif(array_key_exists(14, $user->roles)){
				$role = 'Inspector of Factories (Chemical)';
			}elseif(array_key_exists(17, $user->roles)){
				$role = 'Joint Chief Inspector of Factories (Chemical)';
			}elseif(array_key_exists(30, $user->roles)){
				$role = 'Statistical Cell Incharge';
			}elseif(array_key_exists(31, $user->roles)){
				$role = 'Receiving Cell';
			}			
		}
	}
}

$url_arr = $_SERVER['REQUEST_URI'];
$current_page_arr = explode("/",$url_arr);
$current_page = end($current_page_arr);
?>
<!-- Bootstrap 3.3.7 -->
<link rel="stylesheet" href="<?php  print $base_root.$base_path.'sites/all/themes/custom_dashboard/css/bootstrap.min.css'?>">
<!-- Font Awesome -->
<link rel="stylesheet" href="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/font-awesome/css/font-awesome.css'?>">
<!-- Ionicons -->
<!--<link rel="stylesheet" href="css/ionicons.min.css">-->
<!-- jvectormap -->
<!--<link rel="stylesheet" href="bower_components/jvectormap/jquery-jvectormap.css">-->
<!-- Theme style -->
<link rel="stylesheet" href="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/css/factory.min.css'?>">
<!-- AdminLTE Skins. Choose a skin from the css/skins
       folder instead of downloading all of them to reduce the load. -->
<link rel="stylesheet" href="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/css/_all-skins.min.css'?>">
<!-- Google Font -->
<link href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:200,200i,300,300i,400,400i,600,600i,700,700i,900,900i" rel="stylesheet">

<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/custom_dashboard/js/jquery-1.9.1.js"></script> 
<link href="<?php print $base_root.$base_path?>sites/all/themes/custom_dashboard/css/bootstrap-datepicker.css" rel="stylesheet">
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/custom_dashboard/js/bootstrap-datepicker.js"></script>
<!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
<!--[if lt IE 9]>
<script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
<script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
<![endif]-->

<style>

/*new css for after login menu*/
.navbar-custom-menu .nav.navbar-nav { float: right; }
.after-login-menu { margin: 0; padding: 0; float: left; list-style: none; }
.after-login-menu li { margin: 0; padding: 0; float: left; padding: 15px 0; }
.after-login-menu li a { color: #fff; font-size: 13px; font-weight: 500; padding: 0 6px 0 10px; text-transform:uppercase; }
.after-login-menu li a:hover { color: #f39c12; }
.after-login-menu li ul.dropdown-menu { margin: 0; padding: 0; background: #b8c7ce; }
.after-login-menu li ul.dropdown-menu li { display: block; margin: 0; padding: 0; width: 100%; border-bottom: 1px dashed #666; }
.after-login-menu li ul.dropdown-menu li a { color: #000; display: block ;padding: 5px; }
.after-login-menu li ul.dropdown-menu li a:hover { background:#f39c12; color: #000; }
.after-login-menu li.dropdown a:after {
    font-family: 'FontAwesome';
    content: "\f0d7";
    position: absolute;
    color: #fff;
    top: 16px;
    right: 0;
    font-size: 8px;
    line-height: 20px;
    transition: all 500ms ease;
    -moz-transition: all 500ms ease;
    -webkit-transition: all 500ms ease;
    -ms-transition: all 500ms ease;
    -o-transition: all 500ms ease;
}
.after-login-menu li.dropdown ul.dropdown-menu a:after { color: transparent; }

</style>
<div class="wrapper">

<header class="main-header"> 
    
    <!-- Logo --> 
    <a href="https://wbfactories.gov.in/" class="logo"> 
    <!-- mini logo for sidebar mini 50x50 pixels --> 
    <span class="logo-mini"><b>D</b>F</span> 
    <!-- logo for regular state and mobile devices --> 
    <span class="logo-lg"><b>Home</b></span> </a> 
    
    <!-- Header Navbar: style can be found in header.less -->
    <nav class="navbar navbar-static-top"> 
	<!-- Sidebar toggle button--> 
	<a href="#" class="sidebar-toggle" data-toggle="push-menu" role="button"> <span class="sr-only">Toggle navigation</span> </a> 

	<ul class="after-login-menu">
      <?php $nav_menu = menu_tree_all_data('main-menu');
                                        foreach($nav_menu as $val){
                                                if(!$val['link']['hidden']){
													$link = drupal_get_path_alias($val['link']['link_path']);
													if($link =='<front>' || $link =='aboutus' || $link =='contact-us'|| $link =='rti'|| $link =='faq' ){
														$hide ='none';
													  }else{
														$hide ='';
													  }

													if( $link == "<front>"){
														$link = "";
													}
                                                    if($val['link']['has_children']){?>
                                                         <li class="dropdown user user-menu"><a href="<?php print $base_root.$base_path.$link;?> class="dropdown-toggle" data-toggle="dropdown"><?php print $val['link']['link_title']?></a>
                                                            <?php
                                                            foreach($val['below'] as $level2_link){
                                                                $level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
																if( $level2_path_link == "<front>"){
																	$level2_path_link = "";
																}
                                                                 if(!empty($val['below'])){?>
                                                                    <ul class="dropdown-menu">
                                                                    <?php foreach($val['below'] as $level2){
                                                                            if(!$level2['link']['hidden']){
                                                                                $level2_path = drupal_get_path_alias($level2['link']['link_path']);
																				if( $level2_path == "<front>"){
																					$level2_path = "";
																				}
                                                                                ?>
                                                                                     <li class="user-footer">
                                                                                        <a  target="_blank" href="<?php print $base_root.$base_path.$level2_path;?>">
                                                                                            <?php print $level2['link']['link_title'];?>
                                                                                        </a>
                                                                                    </li>
                                                                            <?php }
                                                                        }?>
                                                                      </ul>  
                                                             <?php }
                                                                
                                                            }?>
                                                        </li>	
                                                    <?php }else{?>	
                                                            <li style="display: <?php print $hide?>"><a href="<?php print $base_root.$base_path.$link;?>"><?php print $val['link']['link_title']?></a></li>
                                                    <?php $hide =''; }
                                                }
                                        }?>
                                        </ul>
    
    




      
      <!-- Navbar Right Menu -->
      <div class="navbar-custom-menu">
        <ul class="nav navbar-nav">
         
          <!-- <li class="dropdown messages-menu"> <a href="#" class="dropdown-toggle" data-toggle="dropdown"> <i class="fa fa-envelope-o" aria-hidden="true"></i> <span class="label label-success">4</span> </a>
            <ul class="dropdown-menu">
              <li class="header">You have 4 messages</li>
              <li> 
          
                <ul class="menu">
                  <li>
                    <a href="#">
                    <div class="pull-left"><img src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/img/user2-160x160.jpg'?>" class="img-circle" alt="User Image">
                     </div>
                    <h4>Support Team <small><i class="fa fa-clock-o" aria-hidden="true"></i> 5 mins</small> </h4>
                    <p>Why not buy a new awesome theme?</p>
                    </a></li>
         
                  <li><a href="#">
                    <div class="pull-left"><img src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/img/user3-128x128.jpg'?>" class="img-circle" alt="User Image"> </div>
                    <h4>AdminLTE Design Team <small><i class="fa fa-clock-o" aria-hidden="true"></i> 2 hours</small> </h4>
                    <p>Why not buy a new awesome theme?</p>
                    </a></li>
                  <li><a href="#">
                    <div class="pull-left"><img src="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/img/user4-128x128.jpg'?>" class="img-circle" alt="User Image"> </div>
                    <h4> Developers <small><i class="fa fa-clock-o" aria-hidden="true"></i> Today</small> </h4>
                    <p>Why not buy a new awesome theme?</p>
                    </a></li>
                  <li> <a href="#">
                    <div class="pull-left"><img src="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/img/user3-128x128.jpg'?>" class="img-circle" alt="User Image"> </div>
                    <h4> Sales Department <small><i class="fa fa-clock-o" aria-hidden="true"></i> Yesterday</small> </h4>
                    <p>Why not buy a new awesome theme?</p>
                    </a></li>
                  <li><a href="#">
                    <div class="pull-left"><img src="<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/img/user4-128x128.jpg'?>" class="img-circle" alt="User Image"> </div>
                    <h4>Reviewers <small><i class="fa fa-clock-o" aria-hidden="true"></i> 2 days</small> </h4>
                    <p>Why not buy a new awesome theme?</p>
                    </a></li>
                </ul>
              </li>
              <li class="footer"><a href="#">See All Messages</a></li>
            </ul>
          </li> -->
          
          
          <li class="dropdown user user-menu"> <a href="#" class="dropdown-toggle" data-toggle="dropdown"><span class="hidden-xs"><small>Welcome,</small> <?php print $fname;?></span> </a>
            <ul class="dropdown-menu">
        
              <li class="user-header"><p><?php print $fname;?><small><?php print $role;?></small> </p></li>
              
             
              <li class="user-footer">
                <?php if($role!='Applicant'){?><div class="pull-left"><a href="<?php print $base_root.$base_path.'profileupdate'?>" class="btn btn-default">Profile</a></div><?php }?>
                <div class="pull-right"> <a href="<?php print $base_root.$base_path.'user/logout'?>" class="btn btn-default">Sign out</a> </div>
              </li>
            </ul>
          </li>
        
        </ul>
      </div>
    </nav>
     
  </header>
  
<aside class="main-sidebar"> 
    <!-- sidebar: style can be found in sidebar.less -->
    <section class="sidebar"> 
      <!-- Sidebar user panel -->
      <!--<div class="user-panel">
        
        <div class="pull-left info">
          <p><small>Welcome</small> Anirban Chowdhury</p></div>
      </div>-->
      <!-- search form -->
     <!-- <form action="#" method="get" class="sidebar-form">
        <div class="input-group">
          <input type="text" name="q" class="form-control" placeholder="Search...">
          <span class="input-group-btn">
          <button type="submit" name="search" id="search-btn" class="btn btn-flat#"> <i class="fa fa-search"></i> </button>
          </span> </div>
      </form>-->
      <!-- /.search form --> 
      <!-- sidebar menu: : style can be found in sidebar.less -->
      

      <ul class="sidebar-menu" data-widget="tree">
      <?php 
		  if (($user->uid!=0) && array_key_exists(4, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-applicant-menu');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					
					$active_class = '';
					$open_class = '';
					if(trim($current_page)==trim($link)){
						$active_class = 'active';
					}
					
					
					if($val['link']['has_children']){?>
					
						<li class="<?php echo $active_class;?> treeview"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
											<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-file-powerpoint-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						// }?>
						</li>	
					<?php }else{?>	
							<li class="<?php echo $active_class;?>"> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
	
					<?php }
					}
				}
			}?>
      <?php 
	      if (($user->uid!=0) && array_key_exists(7, $user->roles)) {
		  $nav_menu = menu_tree_all_data('menu-cmsmanager');
		  foreach($nav_menu as $val){
			if(!$val['link']['hidden']){
				$link = drupal_get_path_alias($val['link']['link_path']);
				if($val['link']['has_children']){?>
                
					<li class="active treeview menu-open"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
                    
				<?php
                    //foreach($val['below'] as $level2_link){
                        //$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
                         if(!empty($val['below'])){?>
                         
                         
                        <ul class="treeview-menu">
						<?php foreach($val['below'] as $level2){
                                if(!$level2['link']['hidden']){
                                    $level2_path = drupal_get_path_alias($level2['link']['link_path']);
                                    ?>
                                        <li>
                                            <a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> 
                                                <span><?php print $level2['link']['link_title'];?></span>
                                            </a>
                                        </li>
                                <?php }
                            }?>
                          </ul>  
                     <?php }
                                                                
                    // }?>
                    </li>	
				<?php }else{?>	
                		<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span></a></li>

                <?php }
				}
            }
        }?>
      <?php 
	      if (($user->uid!=0) && array_key_exists(9, $user->roles)) {
			  
			  
			 
		  $nav_menu = menu_tree_all_data('menu-factoryinspector-menu');
		  foreach($nav_menu as $val){
			if(!$val['link']['hidden']){
				$link = drupal_get_path_alias($val['link']['link_path']);
				if($val['link']['has_children']){?>
                
					<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
                    
				<?php
                    //foreach($val['below'] as $level2_link){
                        //$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
                         if(!empty($val['below'])){?>
                         
                         
                        <ul class="treeview-menu">
						<?php foreach($val['below'] as $level2){
                                if(!$level2['link']['hidden']){
                                    $level2_path = drupal_get_path_alias($level2['link']['link_path']);
                                    ?>
                                    <li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
                                <?php }
                            }?>
                          </ul>  
                     <?php }
                                                                
                    // }?>
                    </li>	
				<?php }else{?>	
                		<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>

                <?php }
				}
            }
        }?>
	  <?php 
          if (($user->uid!=0) && array_key_exists(10, $user->roles)) {
                  $nav_menu = menu_tree_all_data('menu-deputychief-menu');
                  foreach($nav_menu as $val){
                    if(!$val['link']['hidden']){
                        $link = drupal_get_path_alias($val['link']['link_path']);
                        if($val['link']['has_children']){?>
                        
                            <li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
                            
                        <?php
                            //foreach($val['below'] as $level2_link){
                                //$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
                                 if(!empty($val['below'])){?>
                                 
                                 
                                <ul class="treeview-menu">
                                <?php foreach($val['below'] as $level2){
                                        if(!$level2['link']['hidden']){
                                            $level2_path = drupal_get_path_alias($level2['link']['link_path']);
                                            ?>
                                            <li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
                                        <?php }
                                    }?>
                                  </ul>  
                             <?php }
                                                                        
                             //}?>
                            </li>	
                        <?php }else{?>	
                                <li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
        
                        <?php }
                        }
                    }
                }?>
      <?php 
          if (($user->uid!=0) && array_key_exists(11, $user->roles)) {
                  $nav_menu = menu_tree_all_data('menu-jointchief-menu');
                  foreach($nav_menu as $val){
                    if(!$val['link']['hidden']){
                        $link = drupal_get_path_alias($val['link']['link_path']);
                        if($val['link']['has_children']){?>
                        
                            <li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
                            
                        <?php
                           // foreach($val['below'] as $level2_link){
                                //$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
                                 if(!empty($val['below'])){?>
                                 
                                 
                                <ul class="treeview-menu">
                                <?php foreach($val['below'] as $level2){
                                        if(!$level2['link']['hidden']){
                                            $level2_path = drupal_get_path_alias($level2['link']['link_path']);
                                            ?>
                                            <li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
                                        <?php }
                                    }?>
                                  </ul>  
                             <?php }
                                                                        
                            // }?>
                            </li>	
                        <?php }else{?>	
                                <li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
        
                        <?php }
                        }
                    }
                }?>
      <?php      
          if (($user->uid!=0) && array_key_exists(13, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-deputychief-chemical-menu');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					if($val['link']['has_children']){?>
					
						<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
										<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						// }?>
						</li>	
					<?php }else{?>	
							<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
	
					<?php }
					}
				}
			}?>
      <?php      
          if (($user->uid!=0) && array_key_exists(14, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-inspector-chemical-menu');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					if($val['link']['has_children']){?>
					
						<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
										<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						 //}?>
						</li>	
					<?php }else{?>	
							<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span></a></li>
	
					<?php }
					}
				}
			}?>
            
		<!--- RIMA HOME 25-09-2018 -->
        
      <?php      
          if (($user->uid!=0) && array_key_exists(17, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-jointchief-chemical-menu');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					if($val['link']['has_children']){?>
					
						<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
											<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						// }?>
						</li>	
					<?php }else{?>	
							<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
	
					<?php }
					}
				}
			}?>
            
      <!--- RIMA 19-03-2020 -->
      
      <?php      
          if (($user->uid!=0) && array_key_exists(30, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-statistical-cell');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					if($val['link']['has_children']){?>
					
						<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
											<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						// }?>
						</li>	
					<?php }else{?>	
							<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
	
					<?php }
					}
				}
			}?>

      <?php      
          if (($user->uid!=0) && array_key_exists(31, $user->roles)) {
			  $nav_menu = menu_tree_all_data('menu-receiving-cell');
			  foreach($nav_menu as $val){
				if(!$val['link']['hidden']){
					$link = drupal_get_path_alias($val['link']['link_path']);
					if($val['link']['has_children']){?>
					
						<li class=" treeview menu"><a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-paper-plane-o" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> <span class="pull-right-container"> <i class="fa fa-angle-left pull-right" aria-hidden="true"></i> </span> </a>
						
					<?php
						//foreach($val['below'] as $level2_link){
							//$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
							 if(!empty($val['below'])){?>
							 
							 
							<ul class="treeview-menu">
							<?php foreach($val['below'] as $level2){
									if(!$level2['link']['hidden']){
										$level2_path = drupal_get_path_alias($level2['link']['link_path']);
										?>
											<li><a href="<?php print $base_root.$base_path.$level2_path;?>"><i class="fa fa-circle-o" aria-hidden="true"></i> <span><?php print $level2['link']['link_title'];?></span></a></li>
									<?php }
								}?>
							  </ul>  
						 <?php }
																	
						// }?>
						</li>	
					<?php }else{?>	
							<li> <a href="<?php print $base_root.$base_path.$link;?>"> <i class="fa fa-tachometer" aria-hidden="true"></i> <span><?php print $val['link']['link_title']?></span> </a> </li>
	
					<?php }
					}
				}
			}?>
      </ul>
    </section>
    <!-- /.sidebar --> 
  </aside>
  
<div class="content-wrapper"> 

    <section class="content-header">
      <h1><?php echo $title;?></h1>
      <ol class="breadcrumb">
        <li><a href="#"><i class="fa fa-dashboard" aria-hidden="true"></i> Home</a></li>
        <li class="active">Dashboard</li>
      </ol>
    </section>
    
    <section class="content"> 
      <?php
	 
	 // print_r($user->roles);die();
						$link_segment1	 = '';
						$link_segment2 	 = '';
						$link_segment3 	 = '';
						$link_segment4   = '';
						$service_id      = '';
						$link 			 = $_GET['q'];
						
						$link_arr 		 = explode('/', $link);		
						//print_r($link_arr);die;
							
						//if (($user->uid!=0) && array_key_exists(9, $user->roles)) {
						
					if($link_arr[1] == "part_1" || $link_arr[1] == "inspector-plan" || $link_arr[1] == "deputy-plan" || $link_arr[1] == "joint-plan" || $link_arr[1] == "inspector-chemical-plan" || $link_arr[1] == "deputy-chemical-plan" || $link_arr[1] == "joint-chemical-plan" || $link_arr[1] == "inspector-bklog-plan" || $link_arr[1] == "deputy-bklog-plan" || $link_arr[1] == "joint-bklog-plan" || $link_arr[1] == "regsection" || $link_arr[1] == "ddregistration" || $link_arr[1] == "jdregistration" || $link_arr[1] == "inspectorrenewal" || $link_arr[1] == "deputyrenewal" || $link_arr[1] == "inspectoramendment" || $link_arr[1] == "deputyamendment" || $link_arr[1] == "inspection-report-factories"|| $link_arr[1] == "inspectortransfer-back" || $link_arr[1] == "deputytransfer-back" || $link_arr[1] == "annual-report" || $link_arr[1] == "jdrenewal"|| $link_arr[1] == "tabular-application-details"  || $link_arr[1] == "monthly-report") {
				?>
					   <?php if ($messages): ?>
                        <div id="messages"><div class="section clearfix">
                          <?php print $messages; ?>
                        </div></div> 
                      <?php endif; ?>
                       <?php //print render($title_suffix); ?>
                       <div class="tabs mytab cus-page-tabs-overview">
                	<h2 class="element-invisible">Primary tabs</h2>
                    <ul class="tabs primary custom-tabs">
                     <?php
				
                      if($link_arr[1] == "part_1"){?>
           
                        <li class="<?php if($link_arr[2] == 'default'){ echo 'active';}?>">
							<?php echo l('Part-1', '/ad_observation/part_1/default/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
                        </li>
                        <!-- <li class="<?php// if($link_arr[2] == 'register-inspector-checklist'){ echo 'active';}?>">
							<?php  // echo l('Part-2', '/ad_observation/part_1/register-inspector-checklist/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
                        </li> -->
                        <?php } 
    
    				?>

					<!---------------------PLAN SECTION START ------------------------------->

					<?php if($link_arr[1] == "inspector-plan"){?>

						<li class="<?php if($link_arr[2] == 'factory-caf-information'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/inspector-plan/factory-caf-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-document-information'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/inspector-plan/factory-document-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
						<li class="<?php if($link_arr[2] == 'factory-irregularities-information'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/inspector-plan/factory-irregularities-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-ad'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/inspector-plan/extra-irregularities-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
						<li class="<?php if($link_arr[2] == 'factory-send-authority'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/inspector-plan/factory-send-authority/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>
					
                    <?php if($link_arr[1] == "inspector-bklog-plan"){?>

						<li class="<?php if($link_arr[2] == 'bklog-factory-caf-information'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/inspector-bklog-plan/bklog-factory-caf-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'bklog-factory-document-information'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/inspector-bklog-plan/bklog-factory-document-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
						<li class="<?php if($link_arr[2] == 'bklog-factory-irregularities-information'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/inspector-bklog-plan/bklog-factory-irregularities-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
                        <li class="<?php if($link_arr[2] == 'bklog-extra-irregularities-ad'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/inspector-bklog-plan/bklog-extra-irregularities-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
						<li class="<?php if($link_arr[2] == 'bklog-factory-send-authority'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/inspector-bklog-plan/bklog-factory-send-authority/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>

					
					<?php if($link_arr[1] == "deputy-plan"){?>

						<li class="<?php if($link_arr[2] == 'factory-caf-information-dd'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/deputy-plan/factory-caf-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-document-information-dd'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/deputy-plan/factory-document-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-irregularities-information-dd'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/deputy-plan/factory-irregularities-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
                        
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-dd'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/deputy-plan/extra-irregularities-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
						<li class="<?php if($link_arr[2] == 'factory-send-authority-dd'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/deputy-plan/factory-send-authority-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>
                    
                    <?php if($link_arr[1] == "deputy-bklog-plan"){?>

						<li class="<?php if($link_arr[2] == 'bklog-factory-caf-information-dd'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/deputy-bklog-plan/bklog-factory-caf-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'bklog-factory-document-information-dd'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/deputy-bklog-plan/bklog-factory-document-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'bklog-factory-irregularities-information-dd'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/deputy-bklog-plan/bklog-factory-irregularities-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
                        <li class="<?php if($link_arr[2] == 'bklog-extra-irregularities-dd'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/deputy-bklog-plan/bklog-extra-irregularities-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
						<li class="<?php if($link_arr[2] == 'bklog-factory-send-authority-dd'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/deputy-bklog-plan/bklog-factory-send-authority-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>


					<?php if($link_arr[1] == "joint-plan"){?>

                        <li class="<?php if($link_arr[2] == 'factory-caf-information-jd'){ echo 'active';}?>">
                            <?php echo l('CAF', '/admin/joint-plan/factory-caf-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'factory-document-information-jd'){ echo 'active';}?>">
                            <?php echo l('Documents Informations', '/admin/joint-plan/factory-document-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'factory-irregularities-information-jd'){ echo 'active';}?>">
                            <?php echo l('Observations', '/admin/joint-plan/factory-irregularities-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-jd'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/joint-plan/extra-irregularities-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
                        <li class="<?php if($link_arr[2] == 'factory-send-authority-jd'){ echo 'active';}?>">
                            <?php echo l('Forward', '/admin/joint-plan/factory-send-authority-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

					<?php } ?>
                    
                    <?php if($link_arr[1] == "joint-bklog-plan"){?>

                        <li class="<?php if($link_arr[2] == 'bklog-factory-caf-information-jd'){ echo 'active';}?>">
                            <?php echo l('CAF', '/admin/joint-bklog-plan/bklog-factory-caf-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'bklog-factory-document-information-jd'){ echo 'active';}?>">
                            <?php echo l('Documents Informations', '/admin/joint-bklog-plan/bklog-factory-document-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'bklog-factory-irregularities-information-jd'){ echo 'active';}?>">
                            <?php echo l('Observations', '/admin/joint-bklog-plan/bklog-factory-irregularities-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
                        <li class="<?php if($link_arr[2] == 'bklog-extra-irregularities-jd'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/joint-bklog-plan/bklog-extra-irregularities-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'bklog-factory-send-authority-jd'){ echo 'active';}?>">
                            <?php echo l('Forward', '/admin/joint-bklog-plan/bklog-factory-send-authority-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

					<?php } ?>
                        
                        
                    <?php if($link_arr[1] == "inspector-chemical-plan"){?>

						<li class="<?php if($link_arr[2] == 'factory-caf-information-adch'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/inspector-chemical-plan/factory-caf-information-adch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-document-information-adch'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/inspector-chemical-plan/factory-document-information-adch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
						
						<li class="<?php if($link_arr[2] == 'factory-irregularities-information-adch'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/inspector-chemical-plan/factory-irregularities-information-adch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
                        
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-adch'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/inspector-chemical-plan/extra-irregularities-adch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
						<li class="<?php if($link_arr[2] == 'factory-send-authority-adch'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/inspector-chemical-plan/factory-send-authority-adch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>


					
					<?php if($link_arr[1] == "deputy-chemical-plan"){?>

						<li class="<?php if($link_arr[2] == 'factory-CAF-information-ddch'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/deputy-chemical-plan/factory-caf-information-ddch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-document-information-ddch'){ echo 'active';}?>">
							<?php echo l('Documents Informations', '/admin/deputy-chemical-plan/factory-document-information-ddch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

						<li class="<?php if($link_arr[2] == 'factory-irregularities-information-ddch'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/deputy-chemical-plan/factory-irregularities-information-ddch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>
                        
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-ddch'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/deputy-chemical-plan/extra-irregularities-ddch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
						<li class="<?php if($link_arr[2] == 'factory-send-authority-ddch'){ echo 'active';}?>">
							<?php echo l('Forward', '/admin/deputy-chemical-plan/factory-send-authority-ddch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
						</li>

					<?php } ?>


					<?php if($link_arr[1] == "joint-chemical-plan"){?>

                        <li class="<?php if($link_arr[2] == 'factory-caf-information-jdch'){ echo 'active';}?>">
                            <?php echo l('CAF', '/admin/joint-chemical-plan/factory-caf-information-jdch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'factory-document-information-jdch'){ echo 'active';}?>">
                            <?php echo l('Documents Informations', '/admin/joint-chemical-plan/factory-document-information-jdch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'factory-irregularities-information-jdch'){ echo 'active';}?>">
                            <?php echo l('Observations', '/admin/joint-chemical-plan/factory-irregularities-information-jdch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'extra-irregularities-jdch'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/joint-chemical-plan/extra-irregularities-jdch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
                        <li class="<?php if($link_arr[2] == 'factory-send-authority-jdch'){ echo 'active';}?>">
                            <?php echo l('Forward', '/admin/joint-chemical-plan/factory-send-authority-jdch/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>

					<?php } ?>

			<!--     Plan Admin end menu end    -->

        <!--for e-note registartion----------start-->
                        <?php if($link_arr[1] == "regsection"){?>
           
							<li class="<?php if($link_arr[2] == 'view-register-factory-information'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/regsection/view-register-factory-information/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                       
                         <li class="<?php if($link_arr[2] == 'view-register-documents'){ echo 'active';}?>">
							<?php echo l('Documents Information', '/admin/regsection/view-register-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
						<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
							<?php echo l('Payments Information', '/admin/regsection/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'irregularities-ad'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/regsection/irregularities-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                       <li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/regsection/extra-irregularities/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'send-concern-authority'){ echo 'active';}?>">
							<?php echo l('Forward', 'admin/regsection/send-concern-authority/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                         <!-- <li class="<?php  //if($link_arr[2] == 'obsevation_preview'){ echo 'active';}?>">
							<?php // echo l('Observation Preview', '/admin/regsection/obsevation_preview/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li> -->
                      <?php } 
   
    				?>
                     
    					<?php if($link_arr[1] == "ddregistration"){?>
           
							<li class="<?php if($link_arr[2] == 'view-register-factory-information-dd'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/ddregistration/view-register-factory-information-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                          <li class="<?php if($link_arr[2] == 'view-register-documents-dd'){ echo 'active';}?>">
							<?php echo l('Documents Information', '/admin/ddregistration/view-register-documents-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'view-payments-data-dd'){ echo 'active';}?>">
							<?php echo l('Payments Information', '/admin/ddregistration/view-payments-data-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                      
                         <li class="<?php if($link_arr[2] == 'irregularities-dd'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/ddregistration/irregularities-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
                          <li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/ddregistration/extra-irregularities/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						  <li class="<?php if($link_arr[2] == 'send-concern-authority-dd'){ echo 'active';}?>">
							<?php echo l('Forward', 'admin/ddregistration/send-concern-authority-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                        
                      <?php } ?>
    
      				<?php if($link_arr[1] == "jdregistration"){?>
           
							<li class="<?php if($link_arr[2] == 'view-register-factory-information-jd'){ echo 'active';}?>">
							<?php echo l('CAF', '/admin/jdregistration/view-register-factory-information-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                       
                       
                       
                        
                         <li class="<?php if($link_arr[2] == 'view-register-documents-jd/'){ echo 'active';}?>">
							<?php echo l('Documents Information', '/admin/jdregistration/view-register-documents-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						
						<li class="<?php if($link_arr[2] == 'view-payments-data-jd'){ echo 'active';}?>">
							<?php echo l('Payments Information', '/admin/jdregistration/view-payments-data-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                          <li class="<?php if($link_arr[2] == 'irregularities-jd'){ echo 'active';}?>">
							<?php echo l('Observations', '/admin/jdregistration/irregularities-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						  <li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
							<?php echo l('Other Observations', '/admin/jdregistration/extra-irregularities/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
						  <li class="<?php if($link_arr[2] == 'send-concern-authority-jd'){ echo 'active';}?>">
							<?php echo l('Forward', 'admin/jdregistration/send-concern-authority-jd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li>
                         <!-- <li class="<?php // if($link_arr[2] == 'obsevation-preview-dd'){ echo 'active';}?>">
							<?php // echo l('Observation Preview', '/admin/ddregistration/obsevation-preview-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
                        </li> -->
                      <?php } ?>				
    				
                    
                  
					  <?php if($link_arr[1] == "inspectorrenewal"){?>
           
									<li class="<?php if($link_arr[2] == 'view-renewal-inspector'){ echo 'active';}?>">
										<?php echo l('CAF', '/admin/inspectorrenewal/view-renewal-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<li class="<?php if($link_arr[2] == 'view-renewal-documents'){ echo 'active';}?>">
										<?php echo l('Documents Information', '/admin/inspectorrenewal/view-renewal-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<!-- <li class="<?php  //if($link_arr[2] == 'view-renewal-amendment-data'){ echo 'active';}?>">
										<?php // echo l('Amendment Information', '/admin/inspectorrenewal/view-renewal-amendment-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li> -->
									
									<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
										<?php echo l('Payments Information', '/admin/inspectorrenewal/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>
									<li class="<?php if($link_arr[2] == 'irregularities-reneal-ad'){ echo 'active';}?>">
										<?php echo l('Observations', '/admin/inspectorrenewal/irregularities-reneal-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>
                                    
                                  <li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
										<?php echo l('Other Observations', '/admin/inspectorrenewal/extra-irregularities/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<li class="<?php if($link_arr[2] == 'send-concern-renewal-inspector'){ echo 'active';}?>">
										<?php echo l('Forward', '/admin/inspectorrenewal/send-concern-renewal-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

							<?php } ?>				


							<?php if($link_arr[1] == "deputyrenewal"){?>

								<li class="<?php if($link_arr[2] == 'view-renewal-deputy'){ echo 'active';}?>">
									<?php echo l('CAF', '/admin/deputyrenewal/view-renewal-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

								<li class="<?php if($link_arr[2] == 'view-renewal-documents'){ echo 'active';}?>">
									<?php echo l('Documents Information', '/admin/deputyrenewal/view-renewal-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

							
								
								<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
									<?php echo l('Payments Information', '/admin/deputyrenewal/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>
								<li class="<?php if($link_arr[2] == 'irregularities-reneal-dd'){ echo 'active';}?>">
									<?php echo l('Observations', '/admin/deputyrenewal/irregularities-reneal-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>
                                
                                 	<li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
										<?php echo l('Other Observations', '/admin/deputyrenewal/extra-irregularities/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

								<li class="<?php if($link_arr[2] == 'send-concern-renewal-deputy'){ echo 'active';}?>">
									<?php echo l('Forward', '/admin/deputyrenewal/send-concern-renewal-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

							<?php } ?>
								
							<?php if($link_arr[1] == "inspectoramendment"){?>
           
								<li class="<?php if($link_arr[2] == 'view-amendment-inspector'){ echo 'active';}?>">
									<?php echo l('CAF', '/admin/inspectoramendment/view-amendment-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

								<li class="<?php if($link_arr[2] == 'view-amendment-documents'){ echo 'active';}?>">
									<?php echo l('Documents Information', '/admin/inspectoramendment/view-amendment-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

								<!-- <li class="<?php  //if($link_arr[2] == 'view-amendment-amendment-data'){ echo 'active';}?>">
									<?php // echo l('Amendment Information', '/admin/inspectoramendment/view-amendment-amendment-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li> -->
								
								<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
									<?php echo l('Payments Information', '/admin/inspectoramendment/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>
								<li class="<?php if($link_arr[2] == 'irregularities-reneal-ad'){ echo 'active';}?>">
									<?php echo l('Observations', '/admin/inspectoramendment/irregularities-reneal-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

								<li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
										<?php echo l('Other Observations', '/admin/inspectoramendment/extra-irregularities-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

								<li class="<?php if($link_arr[2] == 'send-concern-amendment-inspector'){ echo 'active';}?>">
									<?php echo l('Forward', '/admin/inspectoramendment/send-concern-amendment-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
								</li>

									<?php } ?>				
  <?php if($link_arr[1] == "jdrenewal"){?>
           
									<li class="<?php if($link_arr[2] == 'view-renewal-inspector'){ echo 'active';}?>">
										<?php echo l('CAF', '/admin/jdrenewal/view-renewal-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<li class="<?php if($link_arr[2] == 'view-renewal-documents'){ echo 'active';}?>">
										<?php echo l('Documents Information', '/admin/jdrenewal/view-renewal-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									
									
									<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
										<?php echo l('Payments Information', '/admin/jdrenewal/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>
									<li class="<?php if($link_arr[2] == 'irregularities-reneal-ad'){ echo 'active';}?>">
										<?php echo l('Observations', '/admin/jdrenewal/irregularities-reneal-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>
                                    
                                 

							<?php } ?>	

								<?php if($link_arr[1] == "deputyamendment"){?>

									<li class="<?php if($link_arr[2] == 'view-amendment-deputy'){ echo 'active';}?>">
										<?php echo l('CAF', '/admin/deputyamendment/view-amendment-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<li class="<?php if($link_arr[2] == 'view-amendment-documents'){ echo 'active';}?>">
										<?php echo l('Documents Information', '/admin/deputyamendment/view-amendment-documents/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<!-- <li class="<?php  //if($link_arr[2] == 'view-amendment-amendment-data'){ echo 'active';}?>">
										<?php // echo l('Amendment Information', '/admin/deputyamendment/view-amendment-amendment-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li> -->
									
									<li class="<?php if($link_arr[2] == 'view-payments-data'){ echo 'active';}?>">
										<?php echo l('Payments Information', '/admin/deputyamendment/view-payments-data/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>
									<li class="<?php if($link_arr[2] == 'irregularities-reneal-dd'){ echo 'active';}?>">
										<?php echo l('Observations', '/admin/deputyamendment/irregularities-reneal-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

									<li class="<?php if($link_arr[2] == 'extra-irregularities'){ echo 'active';}?>">
										<?php echo l('Other Observations', '/admin/deputyamendment/extra-irregularities-dd/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>


									<li class="<?php if($link_arr[2] == 'send-concern-amendment-deputy'){ echo 'active';}?>">
										<?php echo l('Forward', '/admin/deputyamendment/send-concern-amendment-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
									</li>

								<?php } ?>
						
                    
               
        <!--for e-note registartion----------END-->             
	<!--for inspection report start-->
						<?php
				
							if($link_arr[1] == "inspection-report-factories") { 
								
								if(empty($title)) {
									$title = "<div style='font-size: 24px; font-weight: bold; color: #2e5cb8;'>Inspection Report (Under The Factories Act, 1948)</div>";
								}
								echo  $title;
						?>
                    	
                        <li class="<?php if($link_arr[2] == 'default' || $link_arr[2] == ''){ echo 'active';}?>">
                            <?php  echo l('Factory Information', '/admin/inspection-report-factories/default/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'workers-details'){ echo 'active';}?>">
                            <?php  echo l('Workers Details', '/admin/inspection-report-factories/workers-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'occupier-details'){ echo 'active';}?>">
                            <?php  echo l('Occupier Details', '/admin/inspection-report-factories/occupier-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'manager-details'){ echo 'active';}?>">
                            <?php  echo l('Manager Details', '/admin/inspection-report-factories/manager-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'infringement-details'){ echo 'active';}?>">
                            <?php  echo l('Infringements', '/admin/inspection-report-factories/infringement-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'remarks-details'){ echo 'active';}?>">
                            <?php  echo l('Remarks', '/admin/inspection-report-factories/remarks-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'insp-report-app-preview'){ echo 'active';}?>">
                            <?php  echo l('Inspection Report Preview', '/admin/inspection-report-factories/insp-report-app-preview/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5]);?>
                        </li>
                        
				<?php 
					}
					 
				?>
	<!--for inspection report end-->



		<!--for Transfer  start-->
		<?php
				
				if($link_arr[1] == "inspectortransfer-back") { 
					
					if(empty($title)) {
						$title = "<div style='font-size: 24px; font-weight: bold; color: #2e5cb8;'>Transfer of licence (Under The Factories Act, 1948)</div>";
					}
					//echo  $title;
			?>
			
			<li class="<?php if($link_arr[2] == 'view-amendment-inspector' || $link_arr[2] == ''){ echo 'active';}?>">
				<?php  echo l('CAF', '/admin/inspectortransfer-back/view-amendment-inspector/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'doc-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Documents Details', '/admin/inspectortransfer-back/doc-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'payment-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Payment information', '/admin/inspectortransfer-back/payment-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			

			<li class="<?php if($link_arr[2] == 'irregularities-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Observations', '/admin/inspectortransfer-back/irregularities-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>

			<li class="<?php if($link_arr[2] == 'extra-irregularities-ad'){ echo 'active';}?>">
				<?php  echo l('Other Observations', 'admin/inspectortransfer-back/extra-irregularities-ad/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'forword-transfer-application'){ echo 'active';}?>">
				<?php  echo l('Forword', '/admin/inspectortransfer-back/forword-transfer-application/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			
			
	<?php 
		}
		 
	?>


<?php
				
				if($link_arr[1] == "deputytransfer-back") { 
					
					if(empty($title)) {
						$title = "<div style='font-size: 24px; font-weight: bold; color: #2e5cb8;'>Transfer of licence (Under The Factories Act, 1948)</div>";
					}
					//echo  $title;
			?>
			
			<li class="<?php if($link_arr[2] == 'view-transfer-deputy' || $link_arr[2] == ''){ echo 'active';}?>">
				<?php  echo l('CAF', '/admin/deputytransfer-back/view-transfer-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'doc-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Documents Details', '/admin/deputytransfer-back/doc-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'payment-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Payment information', '/admin/deputytransfer-back/payment-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>

			<li class="<?php if($link_arr[2] == 'irregularities-transfer-details'){ echo 'active';}?>">
				<?php  echo l('Observations', '/admin/deputytransfer-back/irregularities-transfer-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>

			<li class="<?php if($link_arr[2] == 'extra-irregularities-deputy'){ echo 'active';}?>">
				<?php  echo l('Extra Observations', '/admin/deputytransfer-back/extra-irregularities-deputy/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'forword-transfer-application'){ echo 'active';}?>">
				<?php  echo l('Forword', '/admin/deputytransfer-back/forword-transfer-application/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6]);?>
			</li>
			
			
			
	<?php 
		}
		 
	?>

<!--for Transfer end-->
<?php
				
			if($link_arr[1] == "tabular-application-details") { 
				if(empty($title)) {
					$title = "<div style='font-size: 24px; font-weight: bold; color: #2e5cb8;'>Details of application view (Under The Factories Act, 1948)</div>";
				}
			?>
			
			<li class="<?php if($link_arr[2] == 'view-basic-details-application' || $link_arr[2] == ''){ echo 'active';}?>">
				<?php  echo l('Basic details', '/admin/tabular-application-details/view-basic-details-application/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'view-document-details-application'){ echo 'active';}?>">
				<?php  echo l('Documents Details', '/admin/tabular-application-details/view-document-details-application/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
			</li>
			
			<li class="<?php if($link_arr[2] == 'payment-details'){ echo 'active';}?>">
				<?php  echo l('Payment information', '/admin/tabular-application-details/payment-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
			</li>

			<li class="<?php if($link_arr[2] == 'irregularities-details'){ echo 'active';}?>">
				<?php  echo l('Observations', '/admin/tabular-application-details/irregularities-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
			</li>

			<li class="<?php if($link_arr[2] == 'extra-irregularities-details'){ echo 'active';}?>">
				<?php  echo l('Extra Observations', '/admin/tabular-application-details/extra-irregularities-details/'.$link_arr[3].'/'.$link_arr[4].'/'.$link_arr[5].'/'.$link_arr[6].'/'.$link_arr[7]);?>
			</li>
			
			
			
			
	<?php 
		}
		 
	?>


<!-- annual Report -->
			
    				
              

              <?php 
			  
			  
			  if($link_arr[1] == "annual-report"){


                 

              	?>
           
              <li class="<?php if($link_arr[2] == 'step1' || $link_arr[2] == ''){ echo 'active';}?>">
                            <?php  echo l('STEP1', '/admin/annual-report/step1/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step2'){ echo 'active';}?>">
                            <?php  echo l('STEP2', '/admin/annual-report/step2/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step3'){ echo 'active';}?>">
                            <?php  echo l('STEP3', '/admin/annual-report/step3/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step4'){ echo 'active';}?>">
                            <?php  echo l('STEP4', '/admin/annual-report/step4/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step5'){ echo 'active';}?>">
                            <?php  echo l('STEP5', '/admin/annual-report/step5/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step6'){ echo 'active';}?>">
                            <?php  echo l('STEP6', '/admin/annual-report/step6/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step7'){ echo 'active';}?>">
                            <?php  echo l('STEP7', '/admin/annual-report/step7/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step8'){ echo 'active';}?>">
                            <?php  echo l('STEP8', '/admin/annual-report/step8/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step9'){ echo 'active';}?>">
                            <?php  echo l('STEP9', '/admin/annual-report/step9/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step10'){ echo 'active';}?>">
                            <?php  echo l('STEP10', '/admin/annual-report/step10/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step11'){ echo 'active';}?>">
                            <?php  echo l('STEP11', '/admin/annual-report/step11/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step12'){ echo 'active';}?>">
                            <?php  echo l('STEP12', '/admin/annual-report/step12/'.$link_arr[3]);?>
                        </li>
                          <?php //print "sssssssssssssssssssssssss".$link_arr[3] ;?>
                         <li class="<?php if($link_arr[2] == 'step13'){ echo 'active';}?>">
                            <?php  echo l('View & Submit', '/admin/annual-report/step13/'.$link_arr[3]);?>
                        </li>
                         
                      <?php } ?>

<!-- annual report end-->


<!-- Monthly report -->

          <?php

                 if($link_arr[1] == "monthly-report"){

                     
                      if(array_key_exists(14, $user->roles)){

                      ?>  

                      <li class="<?php if($link_arr[2] == '' || $link_arr[2] == 'step1'){ echo 'active';}?>">
                            <?php  echo l('STEP1', '/admin/monthly-report/step1/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step2'){ echo 'active';}?>">
                            <?php  echo l('STEP2', '/admin/monthly-report/step2/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step6'){ echo 'active';}?>">
                            <?php  echo l('STEP3', '/admin/monthly-report/step6/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step16'){ echo 'active';}?>">
                            <?php  echo l('STEP4', '/admin/monthly-report/step16/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step12'){ echo 'active';}?>">
                            <?php  echo l('STEP5', '/admin/monthly-report/step12/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step17'){ echo 'active';}?>">
                            <?php  echo l('View & Submit', '/admin/monthly-report/step17/'.$link_arr[3]);?>
                        </li>

                    <?php 
                    } 

                    elseif(array_key_exists(15, $user->roles)) {

                      ?>

                      <li class="<?php if($link_arr[2] == '' || $link_arr[2] == 'step1'){ echo 'active';}?>">
                            <?php  echo l('STEP1', '/admin/monthly-report/step1/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step2'){ echo 'active';}?>">
                            <?php  echo l('STEP2', '/admin/monthly-report/step2/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step15'){ echo 'active';}?>">
                            <?php  echo l('STEP3', '/admin/monthly-report/step15/'.$link_arr[3]);?>
                        </li>

                        <li class="<?php if($link_arr[2] == 'step5'){ echo 'active';}?>">
                            <?php  echo l('STEP4', '/admin/monthly-report/step5/'.$link_arr[3]);?>
                        </li>

                         
                         <li class="<?php if($link_arr[2] == 'step12'){ echo 'active';}?>">
                            <?php  echo l('STEP5', '/admin/monthly-report/step12/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step9'){ echo 'active';}?>">
                            <?php  echo l('STEP6', '/admin/monthly-report/step9/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step10'){ echo 'active';}?>">
                            <?php  echo l('STEP7', '/admin/monthly-report/step10/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step17'){ echo 'active';}?>">
                            <?php  echo l('View & Submit', '/admin/monthly-report/step17/'.$link_arr[3]);?>
                        </li>

                 <?php
                    }

                    elseif(array_key_exists(9, $user->roles))
                     {

                      ?>

                    <li class="<?php if($link_arr[2] == '' || $link_arr[2] == 'step1'){ echo 'active';}?>">
                            <?php  echo l('STEP1', '/admin/monthly-report/step1/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step2'){ echo 'active';}?>">
                            <?php  echo l('STEP2', '/admin/monthly-report/step2/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step3'){ echo 'active';}?>">
                            <?php  echo l('STEP3', '/admin/monthly-report/step3/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step4'){ echo 'active';}?>">
                            <?php  echo l('STEP4', '/admin/monthly-report/step4/'.$link_arr[3]);?>
                        </li>
                        
                        <li class="<?php if($link_arr[2] == 'step5'){ echo 'active';}?>">
                            <?php  echo l('STEP5', '/admin/monthly-report/step5/'.$link_arr[3]);?>
                        </li>

                         <li class="<?php if($link_arr[2] == 'step6'){ echo 'active';}?>">
                            <?php  echo l('STEP6', '/admin/monthly-report/step6/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step7'){ echo 'active';}?>">
                            <?php  echo l('STEP7', '/admin/monthly-report/step7/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step8'){ echo 'active';}?>">
                            <?php  echo l('STEP8', '/admin/monthly-report/step8/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step9'){ echo 'active';}?>">
                            <?php  echo l('STEP9', '/admin/monthly-report/step9/'.$link_arr[3]);?>
                        </li>
                         <li class="<?php if($link_arr[2] == 'step10'){ echo 'active';}?>">
                            <?php  echo l('STEP10', '/admin/monthly-report/step10/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step11'){ echo 'active';}?>">
                            <?php  echo l('STEP11', '/admin/monthly-report/step11/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step12'){ echo 'active';}?>">
                            <?php  echo l('STEP12', '/admin/monthly-report/step12/'.$link_arr[3]);?>
                        </li>
                          <?php //print "sssssssssssssssssssssssss".$link_arr[3] ;?>
                         <li class="<?php if($link_arr[2] == 'step13'){ echo 'active';}?>">
                            <?php  echo l('STEP13', '/admin/monthly-report/step13/'.$link_arr[3]);?>
                        </li>
                        <li class="<?php if($link_arr[2] == 'step14'){ echo 'active';}?>">
                            <?php  echo l('STEP14', '/admin/monthly-report/step14/'.$link_arr[3]);?>
                        </li>
                        
                        
                        <li class="<?php if($link_arr[2] == 'step17'){ echo 'active';}?>">
                            <?php  echo l('View & Submit', '/admin/monthly-report/step17/'.$link_arr[3]);?>
                        </li>

                    <?php 
                  }
                  } 
                  ?>  
<!-- monthly end  -->


	
    
     </ul>
            		<?php print render($page['content']); ?>
                    </div>
              
					 <?php	}
					
					  else{?>
                	<div class="container">
					   <?php if ($messages): ?>
                        <div id="messages"><div class="section clearfix">
                          <?php print $messages; ?>
                        </div></div> <!-- /.section, /#messages -->
                      <?php endif; ?>
                      </div>
                	<?php print render($page['content']); ?>
                <?php }?>
    
    
    <!-- /.content --> 
  </section>
</div>

<footer class="main-footer"><?php print render($page['footer']); ?></footer>

</div> 

<!--<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/js/jquery.min.js'?>"></script> -->
<!-- Bootstrap 3.3.7 --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/js/bootstrap.min.js'?>"></script> 
<!-- FastClick --> 
<!--<script src="bower_components/fastclick/lib/fastclick.js"></script>--> 
<!-- AdminLTE App --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/js/adminlte.min.js'?>"></script> 
<!-- Sparkline --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/bower_components/jquery-sparkline/dist/jquery.sparkline.min.js'?>"></script> 
<!-- jvectormap  --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/plugins/jvectormap/jquery-jvectormap-1.2.2.min.js'?>"></script> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/plugins/jvectormap/jquery-jvectormap-world-mill-en.js'?>"></script> 
<!-- SlimScroll --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/bower_components/jquery-slimscroll/jquery.slimscroll.min.js'?>"></script> 
<!-- ChartJS --> 
<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/bower_components/chart.js/Chart.js'?>"></script> 
<!-- AdminLTE dashboard demo (This is only for demo purposes) --> 
<!--<script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/js/pages/dashboard2.js'?>"></script> -->
<!-- AdminLTE for demo purposes --> 
<?php /*?><script src= "<?php print $base_root.$base_path.'sites/all/themes/custom_dashboard/dist/js/demo.js'?>"></script> <?php */?>


<script type="text/javascript">
jQuery('#dateofbirth').datepicker({
	//minViewMode: 'years',
	orientation: 'auto',
	autoclose: true,
	format: 'dd-mm-yyyy',
	//endDate: '+0d'
});
</script>>>>>>>>>>>>>>>>>