<?php
/**
 * The header for our theme.
 *
 * This is the template that displays all of the <head> section and everything up until <div id="content">
 *
 * @link https://developer.wordpress.org/themes/basics/template-files/#template-partials
 *
 * @package Akina
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

<?php
if (akina_option('akina_meta') == true) {
	$keywords = '';
	$description = '';
	if ( is_singular() ) {
		$keywords = '';
		$tags = get_the_tags();
		$categories = get_the_category();
		if ($tags) {
			foreach($tags as $tag) {
				$keywords .= $tag->name . ','; 
			};
		};
		if ($categories) {
			foreach($categories as $category) {
				$keywords .= $category->name . ','; 
			};
		};
		$description = mb_strimwidth( str_replace("\r\n", '', strip_tags($post->post_content)), 0, 240, '…');
	} else {
		$keywords = akina_option('akina_meta_keywords');
		$description = akina_option('akina_meta_description');
	};
?>
<meta name="keywords" content="<?php echo $keywords; ?>" />
<meta name="description" content="<?php echo $description; ?>" />
<?php } ?>

<?php wp_head(); ?>

</head>

<body <?php body_class(); ?>>
<section id="main-container">
	 <div class="openNav">
     <div class="iconflat">	 
	     <div class="icon"></div>
		 </div>
		 <div class="site-branding">
		<!-- 如果设置logo则显示，反之显示博客名 -->
		  <?php if (akina_option('akina_logo')):?>
		     <div class="site-title"><a href="<?php bloginfo('url');?>" ><img src="<?php echo akina_option('akina_logo', ''); ?>"></a></div>
		  <?php else :?>
             <h1 class="site-title"><a href="<?php bloginfo('url');?>" ><?php bloginfo('name');?></a></h1>	
          <?php endif ;?>	
        <!-- logo end -->		  
			</div><!-- .site-branding -->
			
	   </div>	
	  
<div id="page" class="site wrapper">

	<header class="site-header" role="banner">
	 <div class="site-top">
		<div class="site-branding">
		<!-- 如果设置logo则显示，反之显示博客名 -->
		  <?php if (akina_option('akina_logo')):?>
		     <div class="site-title"><a href="<?php bloginfo('url');?>" ><img src="<?php echo akina_option('akina_logo', ''); ?>"></a></div>
		  <?php else :?>
             <h1 class="site-title"><a href="<?php bloginfo('url');?>" ><?php bloginfo('name');?></a></h1>	
          <?php endif ;?>	
        <!-- logo end -->		  
			
		</div><!-- .site-branding -->
		<div id="login-reg">
	<?php header_user_menu(); ?>
	</div>
		
		<div class="searchbox">
			<i class="iconfont js-toggle-search iconsearch">&#xe6f0;</i>
		</div> 
		
       <div class="lower">
			 <nav>
				<?php wp_nav_menu( array( 'depth' => 2, 'theme_location' => 'primary', 'container' => false ) ); ?>
				<i class="iconfont show-nav">&#xe613;</i>
			 </nav><!-- #site-navigation -->
			</div>
				
		</div>		
	</header><!-- #masthead -->	
	<div class="blank"></div>		   
	   <div class="headertop">
	<!-- #imgbox -->
		<?php if ( is_home() ){ ?>
		<?php get_template_part('layouts/imgbox'); ?>	
		<?php } ?>
	<!-- #imgbox -->
	</div>
	<!-- #if single padding top -->
		<?php if ( is_single() ){ ?>
			<style type="text/css">.site-content {padding-top:0px !important}</style>
			<?php } ?>
	<!-- #full header - cat&page -->		
		<?php the_fullheader(); ?>
    <div id="content" class="site-content">