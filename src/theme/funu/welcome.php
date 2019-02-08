<?php 

	/**
	 Template Name: welcome
	 */


?><!DOCTYPE html>
<html <?php language_attributes(); ?>>
<head>
<meta charset="<?php bloginfo( 'charset' ); ?>">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title itemprop="name"><?php global $page, $paged;wp_title( '|', true, 'right' );
bloginfo( 'name' );$site_description = get_bloginfo( 'description', 'display' );
if ( $site_description && ( is_home() || is_front_page() ) ) echo " | $site_description";if ( $paged >= 2 || $page >= 2 ) echo ' | ' . sprintf( __( '第 %s 页'), max( $paged, $page ) );?>
</title>
<?php wp_head(); ?>
</head>
<body <?php body_class(); ?>>

<div class="welcome-wrapper">
<header id="we-header">
 <div class="we-branding">
		<!-- 如果设置logo则显示，反之显示博客名 -->
		  <?php if (akina_option('akina_logo')):?>
		     <div class="wesite-title"><a href="<?php bloginfo('url');?>" ><img src="<?php echo akina_option('akina_logo', ''); ?>"></a></div>
		  <?php else :?>
             <h1 class="wesite-title"><a href="<?php bloginfo('url');?>" ><?php bloginfo('name');?></a></h1>	
          <?php endif ;?>	
        <!-- logo end -->	
       <div class="wesite-des">		
			<p><?php echo get_bloginfo ( 'description' );  ?></p>
			</div>
		
			</div>
			
		<div class="admin-login">
		<a href="<?php get_bloginfo('url')?>/wp-admin"><span></span>LOGIN</a>	
		</div>		
			
		
</header>

			
			<ul class="we-content">
			<li class="we-menu1">
			<a href="<?php bloginfo('url');?>"><span class="we-home we-icon"></span>
			           <span class="we-title wtitle">HOME</span>
					   <span class="sub-text">It's Welcome Page</span>
					   <div class="bottom-line"></div>
					   </a>
			</li>
			
			<li class="we-menu2">
			<a href="<?php echo akina_option('about_link', '#'); ?>"><span class="we-about we-icon"></span>
			           <span class="we-title wtitle">about</span>
					   <span class="sub-text">who im i</span>
					   <div class="bottom-line"></div>
					   </a>
			</li>
			
			<li class="we-menu3">
			<a href="<?php echo akina_option('links_link', '#'); ?>"><span class="we-links we-icon"></span>
			           <span class="we-title wtitle">links</span>
					   <span class="sub-text">hi! friends</span>
					   <div class="bottom-line"></div>
					   </a>
			</li>
			
			<li class="we-menu4">
			<a href="<?php echo akina_option('archives_link', '#'); ?>"><span class="we-archives we-icon"></span>
			           <span class="we-title wtitle">archives</span>
					   <span class="sub-text">all my posts</span>
					   <div class="bottom-line"></div>
					   </a>
			</li>		

			<li class="we-menu5">
			<a href="<?php echo akina_option('youset_link', '#'); ?>"><span class="we-youset we-icon"></span>
			           <span class="we-title wtitle"><?php echo akina_option('youset_title', 'works'); ?></span>
					   <span class="sub-text"><?php echo akina_option('youset_des', 'view my projects'); ?></span>
					   <div class="bottom-line"></div>
					   </a>
			</li>
				
			</div>

		<div class="author-box">
		<div class="we-avatar">
		<?php if (akina_option('focus_logo')):?>
		     <div class="header-tou"><a href="<?php bloginfo('url');?>" ><img src="<?php echo akina_option('focus_logo', ''); ?>"></a></div>
		  <?php else :?>
             <div class="header-tou" >
			 <a href="<?php bloginfo('url');?>"><img src="http://7xwpo4.com1.z0.glb.clouddn.com/akinadeaava.jpg"></a>
			 </div>	
          <?php endif ;?>
		  </div>	
		<div class="author-content">
		<div class="we-visible">
		<p>Hello</p>
		<ul>
		<li>My friends !</li>
		<li>Welcome to !</li>
		<li>My blog !</li>
		<li>Thanks !</li>
		</ul>
		</div>	
		</div>	
    </div>	
	
	<div class="we-footer">
		<div class="we-info">
			<?php esc_attr_e('Copyright ©', 'akina'); ?> <?php esc_attr_e(date('Y')); ?> by Fuzzz <?php esc_attr_e('. All rights reserved.', 'akina'); ?>
			<span class="sep"> | </span>
			<?php printf( esc_html__( 'Theme: %1$s by %2$s.', 'akina' ), 'Akina', '<a href="http://www.akina.pw" rel="designer">Fuzzz</a>' ); ?>
			<div class="we-footertext">
			<p><?php echo akina_option('footer_info', ''); ?></p>
			</div>
		</div>
</div>

<?php wp_footer(); ?>

</body>	

<style type="text/css">
body {
    background: #181717 !important;
}

	</style>


