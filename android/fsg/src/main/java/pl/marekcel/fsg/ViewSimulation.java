package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ViewSimulation extends ViewEGL
{
    public static final String LOG_TAG = "ViewSimulation";

    public interface OnFinishedListener
    {
        public void summarize();
    }

    private OnFinishedListener mOnFinishedListener = null;

    /** */
    public ViewSimulation( Context context )
    {
        /////////////////
        super( context );
        /////////////////
    }
    
    /** */
    public ViewSimulation( Context context, AttributeSet attrs )
    {
        ////////////////////////
        super( context, attrs );
        ////////////////////////
    }

    public void setOnFinishedListener( OnFinishedListener onFinishedListener )
    {
        mOnFinishedListener = onFinishedListener;
    }

    /** */
    @Override
    public void surfaceChanged( SurfaceHolder holder, int format, int width, int height )
    {
        Simulation.setResolution( width, height );

        holder.setFixedSize( Simulation.getScaledWidth(),
                             Simulation.getScaledHeight() );

        //////////////////////////////////////////////////////
        super.surfaceChanged( holder, format, width, height );
        //////////////////////////////////////////////////////
    }

    /** */
    @Override
    public boolean onGenericMotionEvent( MotionEvent event )
    {
        if ( Simulation.processGenericMotionEvent( event ) )
        {
            return true;
        }

        return super.onGenericMotionEvent( event );
    }

    /** */
    @Override
    public boolean onKeyDown( int keyCode, KeyEvent event )
    {
        if ( Simulation.processKeyDownEvent( keyCode, event ) )
        {
            return true;
        }

        return super.onKeyDown( keyCode, event );
    }

    /** */
    @Override
    public boolean onKeyUp( int keyCode, KeyEvent event )
    {
        if ( Simulation.processKeyUpEvent( keyCode, event ) )
        {
            return true;
        }

        return super.onKeyUp( keyCode, event );
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

        private double mTimeStep = 0.0;

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
            Simulation.setResolution( width, height );
            Simulation.init();
        }

        /**
         * @param gl
         */
        public void onDrawFrame( GL10 gl )
        {
            mTimeNew  = SystemClock.uptimeMillis();
            mTimeStep = (double)( mTimeNew - mTimeOld ) / 1000.0;
            mTimeOld  = mTimeNew;

            if ( SimNativeLib.isFinished() )
            {
                if ( mOnFinishedListener != null )
                {
                    mOnFinishedListener.summarize();
                }
            }
            else
            {
                Simulation.update( mTimeStep );
            }
        }
    }
}
