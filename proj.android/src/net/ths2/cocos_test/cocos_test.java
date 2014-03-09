/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package net.ths2.cocos_test;

import jp.adlantis.android.AdlantisView;
import jp.adlantis.android.utils.AdlantisUtils;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.view.Gravity;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

public class cocos_test extends Cocos2dxActivity{
	/** AdlantisのパブリッシャーID */
	private final String adlantisPID = "MzE4MTE%3D%0A";
	/** メンバにする必要ないかもだけど、後で表示/非表示とかすると思うんで */
	private LinearLayout adlantisView;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// cocos_test should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	//ここから追加
	@Override
	public void init(){
		super.init();
		//setAdlantisView();
	}
	/**
	 *  Adlantisの広告を表示する
	 *
	 */
	private void setAdlantisView(){
		//レイアウトの作成
		RelativeLayout mainView = new RelativeLayout(this);
		adlantisView = new LinearLayout(this);
		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
				LinearLayout.LayoutParams.FILL_PARENT,
				(int)(50 * getResources().getDisplayMetrics().density));

		layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
		adlantisView.setGravity(Gravity.CENTER_HORIZONTAL);
		adlantisView.setLayoutParams(layoutParams);

		//AdlantisViewのインスタンス作成
		final AdlantisView adView = new AdlantisView(this);
		adView.setPublisherID(adlantisPID);

		//レイアウトに追加
		adlantisView.addView(adView , new LinearLayout.LayoutParams(
				LinearLayout.LayoutParams.FILL_PARENT,
				AdlantisUtils.adHeightPixels(this)
				));
		mainView.addView(adlantisView);

		/*

		*/

		//viewを追加
		this.addContentView(mainView , new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
	}
	//ここまで追加

	static {
		System.loadLibrary("cocos2dcpp");
	}
}
