<?php
//所有设置
function customizer_css() {
    ?>
	<style type="text/css">
<?php 
// Style Settings
if ( akina_option('shownav') == true) { ?>
	.site-top ul { opacity: 1 !important;}
    .site-top .show-nav { display:none !important; }   
<?php }?>
<?php 
// slider
if ( akina_option('headerbg_open') == true) { ?> @media (max-width:1280px) {#centerbg {display:none} }
<?php }?>
<?php 
// slider
if ( akina_option('head_focus') == true) { ?> .headertop{ display: none !important; }
<?php }?>
<?php 
// liststyle
if ( akina_option('list_type') == 'square') { ?>
	.feature img{ border-radius: 0px; !important; }
    .feature i { border-radius: 0px; !important;	}
<?php }?>
<?php 
// menu
if ( akina_option('toggle-menu') == 'no') { ?>
  .comments .comments-main { display:block !important }
  .comments .comments-hidden { display:none !important }
<?php }?>
<?php 
// like
if ( akina_option('post_like') == 'no') { ?> .post-like { display:none !important }
<?php }?>
<?php 
// share
if ( akina_option('post_share') == 'no') { ?> .post-share { display:none !important }
<?php }?>
<?php 
// nextpre
if ( akina_option('post_nepre') == 'no') { ?> .post-squares { display:none !important }
<?php }?>
<?php 
if ( akina_option('post_right') == 'no') { ?>  .open-message { display:none }
<?php }?>

<?php 
// nextpre
if ( akina_option('author_profile') == 'no') { ?> .author-profile { display:none !important }
<?php }?>
<?php  
if ( akina_option('post_header') == true) { ?> h1.entry-title  { color: <?php echo akina_option('post_header'); ?>;}
<?php }?>
<?php 
// notice
if ( akina_option('head_notice') == '0') { ?> .notice { display:none !important }
<?php }?>
<?php 
// preloader
if ( akina_option('preloader') == 'no') { ?> #preloader { display:none !important }
<?php }?>
<?php 
// search
if ( akina_option('top_search') == 'no') { ?> .searchbox { display:none !important }
<?php }?>
<?php 
// headerbg
if ( akina_option('focus_img') == true ) { ?>  #centerbg { background-image: url(<?php echo akina_option('focus_img');?>) }
<?php }?>
<?php 
// pagenav-style
if ( akina_option('pagenav_style') == 'np') { ?>
	.navigator { display:block !important }
    #pagination { display:none !important }
<?php }?>
<?php 
// youset-logo
if ( akina_option('youset_logo') == true) { ?>  .we-youset { background-image: url(<?php echo akina_option('youset_logo'); ?>); }
<?php }?>
<?php 
// donate
if ( akina_option('post_donate') == 'no') { ?> .donate { display:none; }
<?php }?>
<?php 
// wedo
if ( akina_option('wedo') == false) { ?> li.wedonate:after , .wedonate { display:none }
<?php }?>
<?php 
// alido
if ( akina_option('alido') == false) { ?> li.alidonate:after , .alidonate { display:none }
<?php }?>
<?php 
// 如果同时开启则margin
if ( akina_option('alido') && akina_option('wedo')) { ?>  .wedonate img { margin-right:10px }
<?php }?>
<?php 
if ( akina_option('nav_bg')) { ?>  .site-header { background:<?php echo akina_option('nav_bg'); ?> }
<?php }?>
<?php 
if ( akina_option('secnav_bg')) { ?>  .lower li ul , .user_inner ul { background:<?php echo akina_option('secnav_bg'); ?> }
<?php }?>
<?php 
if ( akina_option('nav_link')) { ?>  .site-top ul li a { color:<?php echo akina_option('nav_link'); ?> }
<?php }?>
<?php 
if ( akina_option('hovernav_link')) { ?>  .site-top ul li a:hover { color:<?php echo akina_option('hovernav_link'); ?> }
<?php }?>
<?php 
if ( akina_option('nav_icon')) { ?>  .site-top .show-nav ,  i.iconfont.js-toggle-search.iconsearch , .ex-login i{ color:<?php echo akina_option('nav_icon'); ?> }
<?php }?>
<?php 
if ( akina_option('nav_text')) { ?>  .site-title a { color:<?php echo akina_option('nav_text'); ?> }
<?php }?>
<?php 
if ( akina_option('global_hover')) { ?>  .feature-title span , .feature i { background:<?php echo akina_option('global_hover'); ?> }
<?php }?>
<?php 
if ( akina_option('text_hover')) { ?>  .entry-title a:hover , .entry-content a:hover , .comment h4 a:hover , a:hover , .site-title a:hover , .sorry li a:hover , .site-info a:hover { color:<?php echo akina_option('text_hover'); ?> }
<?php }?>
<?php 
if ( akina_option('scroll_bar')) { ?>  ::-webkit-scrollbar-thumb { background-color:<?php echo akina_option('scroll_bar'); ?> }
<?php }?>
<?php 
if ( akina_option('donate_icon')) { ?>  .donate { border-color:<?php echo akina_option('donate_icon'); ?>} .donate a , .donate a:hover , .author-profile i {color:<?php echo akina_option('donate_icon'); ?>} .donate:hover {box-shadow:0 0 4px <?php echo akina_option('donate_icon'); ?>}
<?php }?>
<?php 
if ( akina_option('com_bon')) { ?>  .comment-respond input[type='submit'] , input.loginbutton { background:<?php echo akina_option('com_bon'); ?> }
<?php }?>
<?php 
if ( akina_option('akina_gotop')) { ?>  .cd-top { background:url(<?php echo akina_option('akina_gotop'); ?>) no-repeat center 50%}
<?php }?>
<?php 
if ( akina_option('login_bgi')) { ?>  .login-main { background-image:url(<?php echo akina_option('login_bgi'); ?>) }
<?php }?>
<?php 
if ( akina_option('login_bgic')) { ?>  .login-main { background:<?php echo akina_option('login_bgic'); ?> }
<?php }?>
<?php 
if ( akina_option('per_info')) { ?>  .focusinfo { display:none }
<?php }?>
<?php 
if ( akina_option('all_other')) { ?>  .ar-time i , span.ar-circle { background:<?php echo akina_option('all_other'); ?>} #archives-temp h3 , span.sitename {color:<?php echo akina_option('all_other'); ?>} .links ul li:before {background-color:<?php echo akina_option('all_other'); ?> }  .links ul li:hover , .link-title {border-color:<?php echo akina_option('all_other'); ?> }
<?php }?>
	</style>
    <?php
}
add_action('wp_head', 'customizer_css');



/*
*ajax点赞
*/
add_action('wp_ajax_nopriv_specs_zan', 'specs_zan');
add_action('wp_ajax_specs_zan', 'specs_zan');
function specs_zan(){
    global $wpdb,$post;
    $id = $_POST["um_id"];
    $action = $_POST["um_action"];
    if ( $action == 'ding'){
        $specs_raters = get_post_meta($id,'specs_zan',true);
        $expire = time() + 99999999;
        $domain = ($_SERVER['HTTP_HOST'] != 'localhost') ? $_SERVER['HTTP_HOST'] : false; // make cookies work with localhost
        setcookie('specs_zan_'.$id,$id,$expire,'/',$domain,false);
        if (!$specs_raters || !is_numeric($specs_raters)) {
            update_post_meta($id, 'specs_zan', 1);
        } 
        else {
            update_post_meta($id, 'specs_zan', ($specs_raters + 1));
        }
        echo get_post_meta($id,'specs_zan',true);
    } 
    die;
}


function get_the_link_items($id = null){
    $bookmarks = get_bookmarks('orderby=date&category=' .$id );
    $output = '';
    if ( !empty($bookmarks) ) {
        $output .= '<ul class="link-items fontSmooth">';
        foreach ($bookmarks as $bookmark) {
            $output .=  '<li class="link-item"><a class="link-item-inner effect-apollo" href="' . $bookmark->link_url . '" title="' . $bookmark->link_description . '" target="_blank" ><span class="sitename">'. $bookmark->link_name .'</span><div class="linkdes">'. $bookmark->link_description .'</div></a></li>';
        }
        $output .= '</ul>';
    }
    return $output;
}

function get_link_items(){
    $linkcats = get_terms( 'link_category' );
    if ( !empty($linkcats) ) {
        foreach( $linkcats as $linkcat){            
            $result .=  '<h3 class="link-title">'.$linkcat->name.'</h3>';
            if( $linkcat->description ) $result .= '<div class="link-description">' . $linkcat->description . '</div>';
            $result .=  get_the_link_items($linkcat->term_id);
        }
    } else {
        $result = get_the_link_items();
    }
    return $result;
}

function shortcode_link(){
    return get_link_items();
}
add_shortcode('bigfalink', 'shortcode_link');

//图片七牛云缓存
add_filter( 'upload_dir', 'wpjam_custom_upload_dir' );
function wpjam_custom_upload_dir( $uploads ) {
	$upload_path = '';
	$upload_url_path = akina_option('qiniu_cdn');

	if ( empty( $upload_path ) || 'wp-content/uploads' == $upload_path ) {
		$uploads['basedir']  = WP_CONTENT_DIR . '/uploads';
	} elseif ( 0 !== strpos( $upload_path, ABSPATH ) ) {
		$uploads['basedir'] = path_join( ABSPATH, $upload_path );
	} else {
		$uploads['basedir'] = $upload_path;
	}

	$uploads['path'] = $uploads['basedir'].$uploads['subdir'];

	if ( $upload_url_path ) {
		$uploads['baseurl'] = $upload_url_path;
		$uploads['url'] = $uploads['baseurl'].$uploads['subdir'];
	}
	return $uploads;
}

// @父评论
add_filter('comment_text', 'comment_add_at_parent');
function comment_add_at_parent($comment_text)
{
    $comment_ID = get_comment_ID();
    $comment    = get_comment($comment_ID);
    if ($comment->comment_parent) {
        $parent_comment = get_comment($comment->comment_parent);
        $comment_text  = preg_replace('/<a href="#comment-([0-9]+)?".*?>(.*?)<\/a>/i','',$comment_text);//去除存在数据库里的@回复
        $comment_text   = '<a href="#comment-' . $comment->comment_parent . '" rel="nofollow" data-id="' . $comment->comment_parent . '" class="cute atreply">@' . $parent_comment->comment_author . '</a> : ' . $comment_text;
    }
    return $comment_text;
}

/**
 * WordPress 添加面包屑导航 
 * 
 */
function cmp_breadcrumbs() {
	$delimiter = '»'; // 分隔符
	$before = '<span class="current">'; // 在当前链接前插入
	$after = '</span>'; // 在当前链接后插入
	if ( !is_home() && !is_front_page() || is_paged() ) {
		echo '<div itemscope itemtype="http://schema.org/WebPage" id="crumbs">'.__( '当前位置:' , 'cmp' );
		global $post;
		$homeLink = home_url();
		echo ' <a itemprop="breadcrumb" href="' . $homeLink . '">' . __( 'Home' , 'cmp' ) . '</a> ' . $delimiter . ' ';
		if ( is_category() ) { // 分类 存档
			global $wp_query;
			$cat_obj = $wp_query->get_queried_object();
			$thisCat = $cat_obj->term_id;
			$thisCat = get_category($thisCat);
			$parentCat = get_category($thisCat->parent);
			if ($thisCat->parent != 0){
				$cat_code = get_category_parents($parentCat, TRUE, ' ' . $delimiter . ' ');
				echo $cat_code = str_replace ('<a','<a itemprop="breadcrumb"', $cat_code );
			}
			echo $before . '' . single_cat_title('', false) . '' . $after;
		} elseif ( is_day() ) { // 天 存档
			echo '<a itemprop="breadcrumb" href="' . get_year_link(get_the_time('Y')) . '">' . get_the_time('Y') . '</a> ' . $delimiter . ' ';
			echo '<a itemprop="breadcrumb"  href="' . get_month_link(get_the_time('Y'),get_the_time('m')) . '">' . get_the_time('F') . '</a> ' . $delimiter . ' ';
			echo $before . get_the_time('d') . $after;
		} elseif ( is_month() ) { // 月 存档
			echo '<a itemprop="breadcrumb" href="' . get_year_link(get_the_time('Y')) . '">' . get_the_time('Y') . '</a> ' . $delimiter . ' ';
			echo $before . get_the_time('F') . $after;
		} elseif ( is_year() ) { // 年 存档
			echo $before . get_the_time('Y') . $after;
		} elseif ( is_single() && !is_attachment() ) { // 文章
			if ( get_post_type() != 'post' ) { // 自定义文章类型
				$post_type = get_post_type_object(get_post_type());
				$slug = $post_type->rewrite;
				echo '<a itemprop="breadcrumb" href="' . $homeLink . '/' . $slug['slug'] . '/">' . $post_type->labels->singular_name . '</a> ' . $delimiter . ' ';
				echo $before . get_the_title() . $after;
			} else { // 文章 post
				$cat = get_the_category(); $cat = $cat[0];
				$cat_code = get_category_parents($cat, TRUE, ' ' . $delimiter . ' ');
				echo $cat_code = str_replace ('<a','<a itemprop="breadcrumb"', $cat_code );
				echo $before . get_the_title() . $after;
			}
		} elseif ( !is_single() && !is_page() && get_post_type() != 'post' ) {
			$post_type = get_post_type_object(get_post_type());
			echo $before . $post_type->labels->singular_name . $after;
		} elseif ( is_attachment() ) { // 附件
			$parent = get_post($post->post_parent);
			$cat = get_the_category($parent->ID); $cat = $cat[0];
			echo '<a itemprop="breadcrumb" href="' . get_permalink($parent) . '">' . $parent->post_title . '</a> ' . $delimiter . ' ';
			echo $before . get_the_title() . $after;
		} elseif ( is_page() && !$post->post_parent ) { // 页面
			echo $before . get_the_title() . $after;
		} elseif ( is_page() && $post->post_parent ) { // 父级页面
			$parent_id  = $post->post_parent;
			$breadcrumbs = array();
			while ($parent_id) {
				$page = get_page($parent_id);
				$breadcrumbs[] = '<a itemprop="breadcrumb" href="' . get_permalink($page->ID) . '">' . get_the_title($page->ID) . '</a>';
				$parent_id  = $page->post_parent;
			}
			$breadcrumbs = array_reverse($breadcrumbs);
			foreach ($breadcrumbs as $crumb) echo $crumb . ' ' . $delimiter . ' ';
			echo $before . get_the_title() . $after;
		} elseif ( is_search() ) { // 搜索结果
			echo $before ;
			printf( __( 'Search Results for: %s', 'cmp' ),  get_search_query() );
			echo  $after;
		} elseif ( is_tag() ) { //标签 存档
			echo $before ;
			printf( __( 'Tag Archives: %s', 'cmp' ), single_tag_title( '', false ) );
			echo  $after;
		} elseif ( is_author() ) { // 作者存档
			global $author;
			$userdata = get_userdata($author);
			echo $before ;
			printf( __( 'Author Archives: %s', 'cmp' ),  $userdata->display_name );
			echo  $after;
		} elseif ( is_404() ) { // 404 页面
			echo $before;
			_e( 'Not Found', 'cmp' );
			echo  $after;
		}
		if ( get_query_var('paged') ) { // 分页
			if ( is_category() || is_day() || is_month() || is_year() || is_search() || is_tag() || is_author() )
				echo sprintf( __( '( Page %s )', 'cmp' ), get_query_var('paged') );
		}
		echo '</div>';
	}
}

//删除自带小工具
function unregister_default_widgets() {
unregister_widget("WP_Widget_Pages");
unregister_widget("WP_Widget_Calendar");
unregister_widget("WP_Widget_Archives");
unregister_widget("WP_Widget_Links");
unregister_widget("WP_Widget_Meta");
unregister_widget("WP_Widget_Search");
unregister_widget("WP_Widget_Text");
unregister_widget("WP_Widget_Categories");
unregister_widget("WP_Widget_Recent_Posts");
unregister_widget("WP_Widget_Recent_Comments");
unregister_widget("WP_Widget_RSS");
unregister_widget("WP_Widget_Tag_Cloud");
unregister_widget("WP_Nav_Menu_Widget");
}
add_action("widgets_init", "unregister_default_widgets", 11);

//自定义表情路径
function custom_smilies_src($src, $img){return get_bloginfo('template_directory').'/images/smilies/' . $img;}
add_filter('smilies_src', 'custom_smilies_src', 10, 2);

function disable_emoji9s_tinymce($plugins) {
    if (is_array($plugins)) {
        return array_diff($plugins, array(
            'wpemoji'
        ));
    } else {
        return array();
    }
}

function init_akinasmilie() {
    global $wpsmiliestrans;
    //默认表情文本与表情图片的对应关系(可自定义修改)
    $wpsmiliestrans = array(
        ':mrgreen:' => 'icon_mrgreen.gif',
        ':neutral:' => 'icon_neutral.gif',
        ':twisted:' => 'icon_twisted.gif',
        ':arrow:' => 'icon_arrow.gif',
        ':shock:' => 'icon_eek.gif',
        ':smile:' => 'icon_smile.gif',
        ':???:' => 'icon_confused.gif',
        ':cool:' => 'icon_cool.gif',
        ':evil:' => 'icon_evil.gif',
        ':grin:' => 'icon_biggrin.gif',
        ':idea:' => 'icon_idea.gif',
        ':oops:' => 'icon_redface.gif',
        ':razz:' => 'icon_razz.gif',
        ':roll:' => 'icon_rolleyes.gif',
        ':wink:' => 'icon_wink.gif',
        ':cry:' => 'icon_cry.gif',
        ':eek:' => 'icon_surprised.gif',
        ':lol:' => 'icon_lol.gif',
        ':mad:' => 'icon_mad.gif',
        ':sad:' => 'icon_sad.gif',
        '8-)' => 'icon_cool.gif',
        '8-O' => 'icon_eek.gif',
        ':-(' => 'icon_sad.gif',
        ':-)' => 'icon_smile.gif',
        ':-?' => 'icon_confused.gif',
        ':-D' => 'icon_biggrin.gif',
        ':-P' => 'icon_razz.gif',
        ':-o' => 'icon_surprised.gif',
        ':-x' => 'icon_mad.gif',
        ':-|' => 'icon_neutral.gif',
        ';-)' => 'icon_wink.gif',
        '8O' => 'icon_eek.gif',
        ':(' => 'icon_sad.gif',
        ':)' => 'icon_smile.gif',
        ':?' => 'icon_confused.gif',
        ':D' => 'icon_biggrin.gif',
        ':P' => 'icon_razz.gif',
        ':o' => 'icon_surprised.gif',
        ':x' => 'icon_mad.gif',
        ':|' => 'icon_neutral.gif',
        ';)' => 'icon_wink.gif',
        ':!:' => 'icon_exclaim.gif',
        ':?:' => 'icon_question.gif',
    );
   
}
add_action('init', 'init_akinasmilie', 5);  


/*
 * 文章，页面头部背景图
 */
function the_fullheader(){
	$t = ''; // 标题
	$full_image_url = wp_get_attachment_image_src(get_post_thumbnail_id(get_the_ID()), 'full'); //缩略图
     if(is_single()){
    $full_image_url = $full_image_url[0];
    if (have_posts()) : while (have_posts()) : the_post();
    $center = 'single-center';
    $header = 'single-header';
    $t .= the_title( '<h1 class="entry-title">', '</h1>', false);
    //$t .='<p class="entry-census">' .get_the_time('Y.m.d'). '</p>';//
    endwhile; endif;
  }elseif(is_page()) {
	 $full_image_url = $full_image_url[0];
	 $t .= the_title( '<h1 class="entry-title">', '</h1>', false);
  }elseif(is_archive()){
    $full_image_url = z_taxonomy_image_url();
    $des = category_description() ? category_description() : ''; // 描述
    $t .= '<h1 class="cat-title">'.single_cat_title('', false).'</h1>';
    $t .= ' <span class="cat-des">'.$des.'</span>';
  }
  if(!is_home() && $full_image_url) : ?>
  <div class="pattern-center">
 
    <div class="pattern-attachment-img" style="background-image: url(<?php echo $full_image_url; ?>)"> </div>
    <header class="pattern-header"><?php echo $t; ?>
	</header>
  </div>
  <?php else :
    echo '<div class=""></div>';
  endif;
 }
 
 /*
 * 获取相邻文章缩略图
 * 特色图 -> 文章图 -> 首页图
 */
// 上一篇
function get_prev_thumbnail_url() { 
  $prev_post = get_previous_post(); 
  if ( has_post_thumbnail($prev_post->ID) ) { 
    $img_src = wp_get_attachment_image_src( get_post_thumbnail_id( $prev_post->ID ), 'large'); 
    return $img_src[0]; // 特色图
  } 
  else { 
    $content = $prev_post->post_content; 
    preg_match_all('/<img.*?(?: |\\t|\\r|\\n)?src=[\'"]?(.+?)[\'"]?(?:(?: |\\t|\\r|\\n)+.*?)?>/sim', $content, $strResult, PREG_PATTERN_ORDER); 
    $n = count($strResult[1]); 
    if($n > 0){ 
      return $strResult[1][0];  // 文章图
    }
  } 
}

// 下一篇
function get_next_thumbnail_url() { 
  $next_post = get_next_post(); 
  if ( has_post_thumbnail($next_post->ID) ) { 
    $img_src = wp_get_attachment_image_src( get_post_thumbnail_id( $next_post->ID ), 'large'); 
    return $img_src[0]; 
  } 
  else { 
    $content = $next_post->post_content; 
    preg_match_all('/<img.*?(?: |\\t|\\r|\\n)?src=[\'"]?(.+?)[\'"]?(?:(?: |\\t|\\r|\\n)+.*?)?>/sim', $content, $strResult, PREG_PATTERN_ORDER); 
    $n = count($strResult[1]); 
    if($n > 0){ 
      return $strResult[1][0];   
    } 
  } 
}

/*
 * 前端登录页
 */
function header_user_menu(){
	$current_user = wp_get_current_user();  //此函数必须将返回值赋给一个数组变量
			if ( 0 == $current_user->ID ) {  
			// Not logged in.  
			} else {  
			// Logged in.  
			}  			
    if (is_user_logged_in()) {
    ?>
	<div class="exloginbox">
    <a href="#" class="user-panel"><?php echo get_avatar( $current_user->user_email, '110' ); ?></a>
	<div class="user_inner">
	<ul>
	<li><a href="<?php bloginfo('url'); ?>/wp-admin/" class="user-manage">管理后台</a></li>
	<li><a href="<?php echo wp_logout_url(home_url()); ?>" class="user-logout">登出</a></li>
	</ul>
	</div>
	</div>
    <?php
    }else{
    ?>
    <div class="ex-login">				
	<a href="<?php echo akina_option('ex_login'); ?>" target="_top">
		<i class="iconfont">&#xe615;</i>
	</a>
	</div>
    <?php
    }
    ?>
<?php }

/*
 * 首页不显示指定的分类文章
 */
if(akina_option('classify_display')){
  function classify_display($query){
    $source = akina_option('classify_display');
    $cats = explode(',', $source);
    $cat = '';
    if ( $query->is_home ) {
      foreach($cats as $k => $v) {
        $cat .= '-'.$v.','; //重组字符串
      }
      $cat = trim($cat,',');
      $query->set( 'cat', $cat);
    }
    return $query;
  }
  add_filter( 'pre_get_posts', 'classify_display' ); 
}



/**
 * Ajax 提示
 */
function err($ErrMsg) {
    header('HTTP/1.1 405 Method Not Allowed');
    header('Content-Type: text/plain;charset=UTF-8');
    echo $ErrMsg;
    exit;
}


/**
 * Ajax 评论
 */
function ajax_commentsss() {

    // Sets up the WordPress Environment
    if($_POST['action'] == 'ajax_comment_post' && 'POST' == $_SERVER['REQUEST_METHOD']) {
        global $wpdb;
        nocache_headers();
        
        $comment_post_ID = isset($_POST['comment_post_ID']) ? (int) $_POST['comment_post_ID'] : 0;
        
        $post = get_post($comment_post_ID);

        if ( empty($post->comment_status) ) {
            do_action('comment_id_not_found', $comment_post_ID);
            err(__('无效的评论。'));
        }

        // get_post_status() will get the parent status for attachments.
        $status = get_post_status($post);

        $status_obj = get_post_status_object($status);

        if ( !comments_open($comment_post_ID) ) {
            do_action('comment_closed', $comment_post_ID);
            err(__('评论已被关闭。'));
        } elseif ( 'trash' == $status ) {
            do_action('comment_on_trash', $comment_post_ID);
            err(__('无效的评论。'));
        } elseif ( !$status_obj->public && !$status_obj->private ) {
            do_action('comment_on_draft', $comment_post_ID);
            err(__('无效的评论。'));
        } elseif ( post_password_required($comment_post_ID) ) {
            do_action('comment_on_password_protected', $comment_post_ID);
            err(__('密码保护。'));
        } else {
            do_action('pre_comment_on_post', $comment_post_ID);
        }

        $comment_author       = ( isset($_POST['author']) )  ? trim(strip_tags($_POST['author'])) : null;
        $comment_author_email = ( isset($_POST['email']) )   ? trim($_POST['email']) : null;
        $comment_author_url   = ( isset($_POST['url']) )     ? trim($_POST['url']) : null;
        $comment_content      = ( isset($_POST['comment']) ) ? trim($_POST['comment']) : null;
        $edit_id              = ( isset($_POST['edit_id']) ) ? $_POST['edit_id'] : null; // 提取 edit_id

        // If the user is logged in
        $user = wp_get_current_user();
        if ( $user->ID ) {
            if ( empty( $user->display_name ) )
                $user->display_name=$user->user_login;
            $comment_author       = $wpdb->escape($user->display_name);
            $comment_author_email = $wpdb->escape($user->user_email);
            $comment_author_url   = $wpdb->escape($user->user_url);
            if ( current_user_can('unfiltered_html') ) {
                if ( wp_create_nonce('unfiltered-html-comment_' . $comment_post_ID) != $_POST['_wp_unfiltered_html_comment'] ) {
                    kses_remove_filters(); // start with a clean slate
                    kses_init_filters(); // set up the filters
                }
            }
        } else {
            if ( get_option('comment_registration') || 'private' == $status )
                err(__('你必须登陆才可评论。'));
        }

        $comment_type = '';

        if ( get_option('require_name_email') && !$user->ID ) {
            if ( 6 > strlen($comment_author_email) || '' == $comment_author )
                err( __('你必须填写邮箱才能继续。') );
            elseif ( !is_email($comment_author_email))
                err( __('你必须填写正确的邮箱地址。') );
        }

        if ( '' == $comment_content )
            err( __('你忘了写评论内容。') );



        // 检查评论重复
        $dupe = "SELECT comment_ID FROM $wpdb->comments WHERE comment_post_ID = '$comment_post_ID' AND ( comment_author = '$comment_author' ";
        if ( $comment_author_email ) $dupe .= "OR comment_author_email = '$comment_author_email' ";
        $dupe .= ") AND comment_content = '$comment_content' LIMIT 1";
        if ( $wpdb->get_var($dupe) ) {
            err(__('你已经发表过相同的内容。'));
        }

        // 限制评论提交的时间
        if ( $lasttime = $wpdb->get_var( $wpdb->prepare("SELECT comment_date_gmt FROM $wpdb->comments WHERE comment_author = %s ORDER BY comment_date DESC LIMIT 1", $comment_author) ) ) { 
        $time_lastcomment = mysql2date('U', $lasttime, false);
        $time_newcomment  = mysql2date('U', current_time('mysql', 1), false);
        $flood_die = apply_filters('comment_flood_filter', false, $time_lastcomment, $time_newcomment);
        if ( $flood_die ) {
            err(__('先休息下，过会在提交你的评论吧。'));
            }
        }

        $comment_parent = isset($_POST['comment_parent']) ? absint($_POST['comment_parent']) : 0;

        $commentdata = compact('comment_post_ID', 'comment_author', 'comment_author_email', 'comment_author_url', 'comment_content', 'comment_type', 'comment_parent', 'user_ID');

        // 检查评论是否处于编辑状态
        if ( $edit_id ){
        $comment_id = $commentdata['comment_ID'] = $edit_id;
        wp_update_comment( $commentdata );
        } else {
        $comment_id = wp_new_comment( $commentdata );
        }

        $comment = get_comment($comment_id);
        do_action('set_comment_cookies', $comment, $user);

        //$location = empty($_POST['redirect_to']) ? get_comment_link($comment_id) : $_POST['redirect_to'] . '#comment-' . $comment_id; //取消原有的刷新重定向
        //$location = apply_filters('comment_post_redirect', $location, $comment);
        //wp_redirect($location);

        $comment_depth = 1;   //为评论的 class 属性准备的
        $tmp_c = $comment;
        while($tmp_c->comment_parent != 0){
            $comment_depth++;
            $tmp_c = get_comment($tmp_c->comment_parent);
        }
        $GLOBALS['comment'] = $comment;
        ?>
        <li <?php comment_class(); ?> id="li-comment-<?php $comment_ID ?>">
                    <div id="comment-<?php comment_ID(); ?>" class="comment_body contents">
                        <div class="profile">
                            <a href="<?php comment_author_url(); ?>"><?php echo get_avatar( $comment, 50 );?></a>
                        </div>                          
                                <section class="commeta">
                                    <div class="left">
                                        <h4 class="author"><a href="<?php comment_author_url(); ?>"><?php echo get_avatar( $comment, 50 );?><?php comment_author(); ?><span class="isauthor" title="<?php esc_attr_e('Author', 'akina'); ?>"><i class="iconfont">&#xe60e;</i></span></a></h4>
                                    </div>
                                    <div class="right">
                                        <div class="info"><time datetime="<?php comment_date('Y-m-d'); ?>"><?php comment_date(get_option('date_format')); ?></time></div>
                                    </div>
                                </section>
                            <div class="body">
                                <?php comment_text(); ?>
                            </div>
                    </div>
                    <hr>
        <?php
        die();
    }else{return;}
}
add_action('init','ajax_commentsss');