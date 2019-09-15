package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ViewUnitEntry extends ViewEGL
{
    public static final String LOG_TAG = "ViewUnitEntry";

    private int mUnitIndex = 0;             ///<

    /** */
    public ViewUnitEntry( Context context )
    {
        /////////////////
        super( context );
        /////////////////
    }

    /** */
    public ViewUnitEntry( Context context, AttributeSet attrs )
    {
        ////////////////////////
        super( context, attrs );
        ////////////////////////
    }

    /** */
    public void setUnitIndex( int unitIndex )
    {
        mUnitIndex = unitIndex;
    }

    /** */
    @Override
    public void surfaceChanged( SurfaceHolder holder, int format, int width, int height )
    {
        //////////////////////////////////////////////////////
        super.surfaceChanged( holder, format, width, height );
        //////////////////////////////////////////////////////
    }

    /**
     * @param translucent
     * @param depth
     * @param stencil
     */
    protected void init( boolean translucent, int depth, int stencil )
    {
        //////////////////////////////////////////
        super.init( translucent, depth, stencil );
        //////////////////////////////////////////

        /* Set the renderer responsible for frame rendering */
        setRenderer( new Renderer() );

        setRenderMode( RENDERMODE_CONTINUOUSLY );
    }

    /** Renderer class. */
    private class Renderer implements GLSurfaceView.Renderer
    {
        private long mTimeNew = 0;
        private long mTimeOld = 0;

        private double mTimeStep = 0.0f;

        /**
         * @param gl
         * @param config
         */
        public void onSurfaceCreated( GL10 gl, EGLConfig config )
        {
            // Do nothing
            gl.glEnable( GL10.GL_DEPTH_TEST );
        }

        /**
         * @param gl
         * @param width width
         * @param height height
         */
        public void onSurfaceChanged( GL10 gl, int width, int height )
        {
            SimNativeLib.initUnitView( width, height, mUnitIndex );
        }

        /**
         * @param gl
         */
        public void onDrawFrame( GL10 gl )
        {
            mTimeNew  = SystemClock.uptimeMillis();
            mTimeStep = (double)( mTimeNew - mTimeOld ) / 1000.0;
            mTimeOld  = mTimeNew;

            SimNativeLib.update( mTimeStep );
        }
    }
}
