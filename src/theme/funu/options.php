<?php
/**
 * A unique identifier is defined to store the options in the database and reference them from the theme.
 * By default it uses the theme name, in lowercase and without spaces, but this can be changed if needed.
 * If the identifier changes, it'll appear as if the options have been reset.
 */
 
 

function optionsframework_option_name() {

	// 从样式表获取主题名称
	$themename = wp_get_theme();
	$themename = preg_replace("/\W/", "_", strtolower($themename) );

	$optionsframework_settings = get_option( 'optionsframework' );
	$optionsframework_settings['id'] = $themename;
	update_option( 'optionsframework', $optionsframework_settings );
}

/**
 * Defines an array of options that will be used to generate the settings page and be saved in the database.
 * When creating the 'id' fields, make sure to use all lowercase and no spaces.
 *
 * If you are making your theme translatable, you should replace 'options_framework_theme'
 * with the actual text domain for your theme.  请阅读:
 * http://codex.wordpress.org/Function_Reference/load_theme_textdomain
 */

function optionsframework_options() {
	// 测试数据
	$test_array = array(
		'one' => __('1', 'options_framework_theme'),
		'two' => __('2', 'options_framework_theme'),
		'three' => __('3', 'options_framework_theme'),
		'four' => __('4', 'options_framework_theme'),
		'five' => __('5', 'options_framework_theme'),
		'six' => __('6', 'options_framework_theme'),
		'seven' => __('7', 'options_framework_theme')
	);
		

	// 复选框数组
	$multicheck_array = array(
		'one' => __('法国吐司', 'options_framework_theme'),
		'two' => __('薄煎饼', 'options_framework_theme'),
		'three' => __('煎蛋', 'options_framework_theme'),
		'four' => __('绉绸', 'options_framework_theme'),
		'five' => __('感化饼干', 'options_framework_theme')
	);

	// 复选框默认值
	$multicheck_defaults = array(
		'one' => '1',
		'five' => '1'
	);

	// 背景默认值
	$background_defaults = array(
		'color' => '',
		'image' => '',
		'repeat' => 'repeat',
		'position' => 'top center',
		'attachment'=>'scroll' );

	// 版式默认值
	$typography_defaults = array(
		'size' => '15px',
		'face' => 'georgia',
		'style' => 'bold',
		'color' => '#bada55' );
		
	// 版式设置选项
	$typography_options = array(
		'sizes' => array( '6','12','14','16','20' ),
		'faces' => array( 'Helvetica Neue' => 'Helvetica Neue','Arial' => 'Arial' ),
		'styles' => array( 'normal' => '普通','bold' => '粗体' ),
		'color' => false
	);

	// 将所有分类（categories）加入数组
	$options_categories = array();
	$options_categories_obj = get_categories();
	foreach ($options_categories_obj as $category) {
		$options_categories[$category->cat_ID] = $category->cat_name;
	}
	
	// 将所有标签（tags）加入数组
	$options_tags = array();
	$options_tags_obj = get_tags();
	foreach ( $options_tags_obj as $tag ) {
		$options_tags[$tag->term_id] = $tag->name;
	}


	// 将所有页面（pages）加入数组
	$options_pages = array();
	$options_pages_obj = get_pages('sort_column=post_parent,menu_order');
	$options_pages[''] = 'Select a page:';
	foreach ($options_pages_obj as $page) {
		$options_pages[$page->ID] = $page->post_title;
	}

	// 如果使用图片单选按钮, define a directory path
	$imagepath =  get_template_directory_uri() . '/images/';

	$options = array();

	//基本设置
	$options[] = array(
		'name' => __('基本设置', 'options_framework_theme'),
		'type' => 'heading');
		
	$options[] = array(
		'name' => __('logo', 'options_framework_theme'),
		'desc' => __('高度尺寸50px。', 'options_framework_theme'),
		'id' => 'akina_logo',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/akina3.png',
		'type' => 'upload');
		
	$options[] = array(
		'name' => __('博主描述', 'options_framework_theme'),
		'desc' => __('一段自我描述的话', 'options_framework_theme'),
		'id' => 'admin_des',
		'std' => 'Carpe Diem and Do what I like',
		'type' => 'textarea');	
	
	$options[] = array(
		'name' => __('自定义关键词和首页描述', 'options_framework_theme'),
		'desc' => __('开启之后可自定义填写关键词和首页描述', 'options_framework_theme'),
		'id' => 'akina_meta',
		'std' => '0',
		'type' => 'checkbox');
		
	$options[] = array(
		'name' => __('关键词', 'options_framework_theme'),
		'desc' => __('各关键字间用半角逗号","分割，数量在5个以内最佳。', 'options_framework_theme'),
		'id' => 'akina_meta_keywords',
		'std' => '',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('首页描述', 'options_framework_theme'),
		'desc' => __('用简洁的文字描述本站点，字数建议在120个字以内。', 'options_framework_theme'),
		'id' => 'akina_meta_description',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('开启PJAX局部刷新', 'options_framework_theme'),
		'desc' => __('原理与Ajax相同', 'options_framework_theme'),
		'id' => 'app_pjax',
		'std' => '0',
		'type' => 'checkbox');
	
		
	$options[] = array(
		'name' => __('是否开启第三方评论插件支持', 'options_framework_theme'),
		'desc' => __('多说于2017年3月停止服务，让我们永远记住它，陪伴我们的这几年', 'options_framework_theme'),
		'id' => 'general_disqus_plugin_support',
		'std' => '0',
		'type' => 'checkbox');		
	
	$options[] = array(
		'name' => __('顶部搜索按钮', 'akina'),
		'id' => 'top_search',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
		
	$options[] = array(
		'name' => __('评论收缩', 'akina'),
		'id' => 'toggle-menu',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
		
	$options[] = array(
		'name' => __('是否开启preloader动画', 'akina'),
		'id' => 'preloader',
		'std' => "no",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
	
	$options[] = array(
		'name' => __('回到顶部图标', 'options_framework_theme'),
		'desc' => __('尺寸务必为50*50px。', 'options_framework_theme'),
		'id' => 'akina_gotop',
		'type' => 'upload');
		
	$options[] = array(
		'name' => __('文章翻页列表样式', 'akina'),
		'id' => 'pagenav_style',
		'std' => "ajax",
		'type' => "radio",
		'options' => array(
			'ajax' => __('ajax加载', ''),
			'np' => __('上一页和下一页', '')
		));	

	$options[] = array(
		'name' => __('页脚信息', 'options_framework_theme'),
		'desc' => __('页脚说明文字', 'options_framework_theme'),
		'id' => 'footer_info',
		'std' => 'Carpe Diem and Do what I like',
		'type' => 'textarea');

	$options[] = array(
		'name' => __('站长统计', 'options_framework_theme'),
		'desc' => __('填写统计代码，将被隐藏', 'options_framework_theme'),
		'id' => 'site_statistics',
		'std' => '',
		'type' => 'textarea');		
	
	
		
	//首页布局	

	$options[] = array(
		'name' => __('首页布局', 'options_framework_theme'),
		'type' => 'heading');

	$options[] = array(
		'name' => __('是否一直显示菜单', 'options_framework_theme'),
		'desc' => __('默认不显示', 'options_framework_theme'),
		'id' => 'shownav',
		'std' => '0',
		'type' => 'checkbox');
	
	$options[] = array(
		'name' => __('是否在移动端显示顶部大图', 'options_framework_theme'),
		'desc' => __('默认显示，勾选关闭', 'options_framework_theme'),
		'id' => 'headerbg_open',
		'std' => '0',
		'type' => 'checkbox');
		
	$options[] = array(
		'name' => __('是否开启顶部focus区', 'options_framework_theme'),
		'desc' => __('默认显示，勾选关闭', 'options_framework_theme'),
		'id' => 'head_focus',
		'std' => '0',
		'type' => 'checkbox');	
	
	$options[] = array(
		'name' => __('focus区背景图', 'options_framework_theme'),
		'desc' => __('高度尺寸1920*1080。', 'options_framework_theme'),
		'id' => 'focus_img',
		'type' => 'upload');

	$options[] = array(
		'name' => __('是否开启顶部个人信息区域', 'options_framework_theme'),
		'desc' => __('默认显示顶部的个人头像，个人描述和社交按钮，勾选关闭', 'options_framework_theme'),
		'id' => 'per_info',
		'std' => '0',
		'type' => 'checkbox');	
		
	 $options[] = array(
		'name' => __('个人头像', 'options_framework_theme'),
		'desc' => __('高度尺寸50px。', 'options_framework_theme'),
		'id' => 'focus_logo',
		'type' => 'upload'); 
		
	$options[] = array(
		'name' => __('是否开启顶公告', 'options_framework_theme'),
		'desc' => __('默认不显示，勾选开启', 'options_framework_theme'),
		'id' => 'head_notice',
		'std' => '0',
		'type' => 'checkbox');	

	$options[] = array(
		'name' => __('顶部公告内容', 'options_framework_theme'),
		'desc' => __('顶部公告内容', 'options_framework_theme'),
		'id' => 'notice_title',
		'std' => '我很荣幸的启用了Akina主题',
		'type' => 'text');	

	$options[] = array(
		'name' => __('首页不显示的分类文章', 'options_framework_theme'),
		'desc' => __('填写分类ID，多个用英文“ , ”分开', 'options_framework_theme'),
		'id' => 'classify_display',
		'std' => '',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('首页列表特色图样式', 'akina'),
		'id' => 'list_type',
		'std' => "round",
		'type' => "radio",
		'options' => array(
			'round' => __('圆形', ''),
			'square' => __('方形', '')
		));	
		
	$options[] = array(
		'name' => __('是否开启聚焦', 'options_framework_theme'),
		'desc' => __('默认开启', 'options_framework_theme'),
		'id' => 'top_feature',
		'std' => '1',
		'type' => 'checkbox');	

	$options[] = array(
		'name' => __('聚焦标题', 'options_framework_theme'),
		'desc' => __('默认为聚焦，你也可以修改为其他，当然不能当广告用！不允许！！', 'options_framework_theme'),
		'id' => 'feature_title',
		'std' => '聚焦',
		'class' => 'mini',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('聚焦图一', 'options_framework_theme'),
		'desc' => __('尺寸257px*160px', 'options_framework_theme'),
		'id' => 'feature1_img',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/akinazhanwei.jpg',
		'type' => 'upload');

	$options[] = array(
		'name' => __('聚焦图一标题', 'options_framework_theme'),
		'desc' => __('聚焦图一标题', 'options_framework_theme'),
		'id' => 'feature1_title',
		'std' => 'feature1',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('聚焦图一链接', 'options_framework_theme'),
		'desc' => __('聚焦图一链接', 'options_framework_theme'),
		'id' => 'feature1_link',
		'std' => '#',
		'type' => 'text');		
		
	$options[] = array(
		'name' => __('聚焦图二', 'options_framework_theme'),
		'desc' => __('尺寸257px*160px', 'options_framework_theme'),
		'id' => 'feature2_img',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/akinazhanwei.jpg',
		'type' => 'upload');

	$options[] = array(
		'name' => __('聚焦图二标题', 'options_framework_theme'),
		'desc' => __('聚焦图二标题', 'options_framework_theme'),
		'id' => 'feature2_title',
		'std' => 'feature2',
		'type' => 'text');

	$options[] = array(
		'name' => __('聚焦图二链接', 'options_framework_theme'),
		'desc' => __('聚焦图二链接', 'options_framework_theme'),
		'id' => 'feature2_link',
		'std' => '#',
		'type' => 'text');		
		
			
	$options[] = array(
		'name' => __('聚焦图三', 'options_framework_theme'),
		'desc' => __('尺寸257px*160px', 'options_framework_theme'),
		'id' => 'feature3_img',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/akinazhanwei.jpg',
		'type' => 'upload');

	$options[] = array(
		'name' => __('聚焦图三标题', 'options_framework_theme'),
		'desc' => __('聚焦图三标题', 'options_framework_theme'),
		'id' => 'feature3_title',
		'std' => 'feature3',
		'type' => 'text');	

	$options[] = array(
		'name' => __('聚焦图三链接', 'options_framework_theme'),
		'desc' => __('聚焦图三链接', 'options_framework_theme'),
		'id' => 'feature3_link',
		'std' => '#',
		'type' => 'text');
			
		
	//文章页	

	$options[] = array(
		'name' => __('文章页', 'options_framework_theme'),
		'type' => 'heading');
			
		
	$options[] = array(
		'name' => __('文章点赞', 'akina'),
		'id' => 'post_like',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
		
	$options[] = array(
		'name' => __('文章分享', 'akina'),
		'id' => 'post_share',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
	
	$options[] = array(
		'name' => __('上一篇下一篇', 'akina'),
		'id' => 'post_nepre',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
	
	$options[] = array(
		'name' => __('版权声明', 'akina'),
		'id' => 'post_right',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
		
	$options[] = array(
		'name' => __('博主信息', 'akina'),
		'id' => 'author_profile',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	
		
	$options[] = array(
		'name' => __('打赏功能', 'akina'),
		'id' => 'post_donate',
		'std' => "yes",
		'type' => "radio",
		'options' => array(
			'yes' => __('开启', ''),
			'no' => __('关闭', '')
		));	

	$options[] = array(
		'name' => __('微信打赏', 'options_framework_theme'),
		'desc' => __('尺寸100px*100px', 'options_framework_theme'),
		'id' => 'wedo',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/wedo.jpg',
		'type' => 'upload');
	
	$options[] = array(
		'name' => __('支付宝打赏', 'options_framework_theme'),
		'desc' => __('尺寸100px*100px', 'options_framework_theme'),
		'id' => 'alido',
		'std' => 'http://7xwpo4.com1.z0.glb.clouddn.com/alido.jpg',
		'type' => 'upload');
		
	//社交选项	

	$options[] = array(
		'name' => __('社交设置', 'options_framework_theme'),
		'type' => 'heading');
		
	
	$options[] = array(
		'name' => __('微信', 'options_framework_theme'),
		'desc' => __('微信二维码', 'options_framework_theme'),
		'id' => 'wechat',
		'type' => 'upload');
	
    $options[] = array(
		'name' => __('新浪微博', 'options_framework_theme'),
		'desc' => __('新浪微博地址', 'options_framework_theme'),
		'id' => 'sina',
		'std' => 'www.fuzzz.cc',
		'type' => 'text');
		
		
	$options[] = array(
		'name' => __('腾讯qq', 'options_framework_theme'),
		'desc' => __('qq号码', 'options_framework_theme'),
		'id' => 'qq',
		'std' => 'www.fuzzz.cc',
		'type' => 'text');
		
	$options[] = array(
		'name' => __('qq空间', 'options_framework_theme'),
		'desc' => __('qq空间地址', 'options_framework_theme'),
		'id' => 'qzone',
		'std' => 'www.fuzzz.cc',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('GitHub', 'options_framework_theme'),
		'desc' => __('GitHub地址', 'options_framework_theme'),
		'id' => 'github',
		'std' => 'www.fuzzz.cc',
		'type' => 'text');

	$options[] = array(
		'name' => __('lofter', 'options_framework_theme'),
		'desc' => __('lofter地址', 'options_framework_theme'),
		'id' => 'lofter',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('bilibili', 'options_framework_theme'),
		'desc' => __('bilibili地址', 'options_framework_theme'),
		'id' => 'bili',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('youku', 'options_framework_theme'),
		'desc' => __('youku地址', 'options_framework_theme'),
		'id' => 'youku',
		'std' => '',
		'type' => 'text');
	
	$options[] = array(
		'name' => __('alipay', 'options_framework_theme'),
		'desc' => __('alipay二维码', 'options_framework_theme'),
		'id' => 'alipay',
		'type' => 'upload');
		
	$options[] = array(
		'name' => __('dribbble', 'options_framework_theme'),
		'desc' => __('dribbble地址', 'options_framework_theme'),
		'id' => 'dribbble',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('tieba', 'options_framework_theme'),
		'desc' => __('tieba地址', 'options_framework_theme'),
		'id' => 'tieba',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('twitter', 'options_framework_theme'),
		'desc' => __('twitter地址', 'options_framework_theme'),
		'id' => 'twitter',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('zcool', 'options_framework_theme'),
		'desc' => __('zcool地址', 'options_framework_theme'),
		'id' => 'zcool',
		'std' => '',
		'type' => 'text');

	$options[] = array(
		'name' => __('zhihu', 'options_framework_theme'),
		'desc' => __('zhihu地址', 'options_framework_theme'),
		'id' => 'zhihu',
		'std' => '',
		'type' => 'text');	
		
	
	$options[] = array(
		'name' => __('颜色设置', 'options_framework_theme'),
		'type' => 'heading');
	
	$options[] = array(
		'name' => __('导航栏背景色', 'options_framework_theme'),
		'desc' => __('顶部导航背景颜色', 'options_framework_theme'),
		'id' => 'nav_bg',
		'std' => '',
		'type' => 'color' );

	$options[] = array(
		'name' => __('二级导航栏背景色', 'options_framework_theme'),
		'desc' => __('顶部二级导航背景颜色', 'options_framework_theme'),
		'id' => 'secnav_bg',
		'std' => '',
		'type' => 'color' );
	
	$options[] = array(
		'name' => __('导航链接颜色', 'options_framework_theme'),
		'desc' => __('导航字体颜色', 'options_framework_theme'),
		'id' => 'nav_link',
		'std' => '',
		'type' => 'color' );
	
	$options[] = array(
		'name' => __('导航链接悬浮颜色', 'options_framework_theme'),
		'desc' => __('导航字体悬浮颜色', 'options_framework_theme'),
		'id' => 'hovernav_link',
		'std' => '',
		'type' => 'color' );

	$options[] = array(
		'name' => __('导航图标颜色', 'options_framework_theme'),
		'desc' => __('汉堡图标和搜索图标的颜色', 'options_framework_theme'),
		'id' => 'nav_icon',
		'std' => '',
		'type' => 'color' );

	$options[] = array(
		'name' => __('导航文字LOGO颜色', 'options_framework_theme'),
		'desc' => __('没有设置图片LOGO时，导航条左侧文字颜色', 'options_framework_theme'),
		'id' => 'nav_text',
		'std' => '',
		'type' => 'color' );
		
	$options[] = array(
		'name' => __('全局HOVER层颜色', 'options_framework_theme'),
		'desc' => __('聚焦图和文章缩略图鼠标悬浮时的颜色', 'options_framework_theme'),
		'id' => 'global_hover',
		'std' => '',
		'type' => 'color' );
		
	$options[] = array(
		'name' => __('全局文字链接HOVER颜色', 'options_framework_theme'),
		'desc' => __('文章标题，内页链接等链接悬浮颜色', 'options_framework_theme'),
		'id' => 'text_hover',
		'std' => '',
		'type' => 'color' );
		
	$options[] = array(
		'name' => __('滚动条颜色', 'options_framework_theme'),
		'desc' => __('右侧滚动条颜色', 'options_framework_theme'),
		'id' => 'scroll_bar',
		'std' => '',
		'type' => 'color' );
	
	$options[] = array(
		'name' => __('打赏图标颜色', 'options_framework_theme'),
		'desc' => __('文章页打赏图标颜色', 'options_framework_theme'),
		'id' => 'donate_icon',
		'std' => '',
		'type' => 'color' );
		
	$options[] = array(
		'name' => __('评论提交按钮颜色', 'options_framework_theme'),
		'desc' => __('提交评论按钮的颜色', 'options_framework_theme'),
		'id' => 'com_bon',
		'std' => '',
		'type' => 'color' );

	$options[] = array(
		'name' => __('页面文字以及图标颜色', 'options_framework_theme'),
		'desc' => __('归档页以及友链页面所有统一颜色', 'options_framework_theme'),
		'id' => 'all_other',
		'std' => '',
		'type' => 'color' );

	//自定义页面
	$options[] = array(
		'name' => __('其他', 'options_framework_theme'),
		'type' => 'heading' );	
	
	$options[] = array(
		'name' => __('前台登录页地址', 'options_framework_theme'),
		'desc' => __('输入你登录页面的链接地址', 'options_framework_theme'),
		'id' => 'ex_login',
		'std' => '',
		'type' => 'text');
	
	$options[] = array(
		'name' => __('登录页面背景色', 'options_framework_theme'),
		'desc' => __('这不用解释吧', 'options_framework_theme'),
		'id' => 'login_bgic',
		'std' => '',
		'type' => 'color' );	
		
	$options[] = array(
		'name' => __('登录页面背景图', 'options_framework_theme'),
		'desc' => __('尺寸自己斟酌', 'options_framework_theme'),
		'id' => 'login_bgi',
		'type' => 'upload');	
	
	$options[] = array(
		'name' => __('作品展示分类', 'options_framework_theme'),
		'desc' => __('填写分类ID，多个用英文“ , ”分开', 'options_framework_theme'),
		'id' => 'works_multicheck',
		'std' => '',
		'type' => 'text');
		
	$options[] = array(
		'name' => __('七牛图片cdn', 'options_framework_theme'),
		'desc' => __('！重要:填写格式为 http://你的二级域名（七牛三级域名）/wp-content/uploads', 'options_framework_theme'),
		'id' => 'qiniu_cdn',
		'std' => '',
		'type' => 'text');	
		
	$options[] = array(
		'name' => __('关于欢迎页', 'options_framework_theme'),
		'desc' => __('页面类型中存在着一个welcome页面，我觉得是很鸡肋的，但是我TM就是要加这个页面，其中前四个是已经固定的模块，第五个可以自定义', 'options_framework_theme'),
		'type' => 'info');
	
	$options[] = array(
		'name' => __('欢迎页自定义模块标题', 'options_framework_theme'),
		'desc' => __('默认是works', 'options_framework_theme'),
		'id' => 'youset_title',
		'std' => 'works',
		'type' => 'text');
		
	$options[] = array(
		'name' => __('欢迎页自定义模块描述', 'options_framework_theme'),
		'desc' => __('随便写', 'options_framework_theme'),
		'id' => 'youset_des',
		'std' => 'view my projects',
		'type' => 'text');
		
	$options[] = array(
		'name' => __('自定义图标', 'options_framework_theme'),
		'desc' => __('64*64。', 'options_framework_theme'),
		'id' => 'youset_logo',
		'type' => 'upload');

	$options[] = array(
		'name' => __('欢迎页自定义模块链接', 'options_framework_theme'),
		'desc' => __('随便写', 'options_framework_theme'),
		'id' => 'youset_link',
		'std' => '#',
		'type' => 'text');	
	
	$options[] = array(
		'name' => __('About页面链接', 'options_framework_theme'),
		'desc' => __('关于我地址链接', 'options_framework_theme'),
		'id' => 'about_link',
		'std' => '#',
		'type' => 'text');		
			
	$options[] = array(
		'name' => __('links页面链接', 'options_framework_theme'),
		'desc' => __('友链页面地址链接', 'options_framework_theme'),
		'id' => 'links_link',
		'std' => '#',
		'type' => 'text');	
	
	$options[] = array(
		'name' => __('archives页面链接', 'options_framework_theme'),
		'desc' => __('归档地址链接', 'options_framework_theme'),
		'id' => 'archives_link',
		'std' => '#',
		'type' => 'text');
		
		
		
		

	return $options;
}