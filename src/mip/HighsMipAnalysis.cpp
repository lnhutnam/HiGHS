/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2024 by Julian Hall, Ivet Galabova,    */
/*    Leona Gottwald and Michael Feldmeier                               */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file simplex/HighsMipAnalysis.cpp
 * @brief
 */
#include "mip/HighsMipAnalysis.h"

#include <cmath>

#include "mip/MipTimer.h"

void HighsMipAnalysis::setup(const HighsLp& lp, const HighsOptions& options) {
  setupMipTime(options);
}

void HighsMipAnalysis::setupMipTime(const HighsOptions& options) {
  analyse_mip_time = true;  // ToDo: Make this conditional
  //      kHighsAnalysisLevelSolverTime & options.highs_analysis_level;
  if (analyse_mip_time) {
    HighsTimerClock clock;
    clock.timer_pointer_ = timer_;
    MipTimer mip_timer;
    mip_timer.initialiseMipClocks(clock);
    mip_clocks = clock;
  }
}

void HighsMipAnalysis::mipTimerStart(const HighsInt mip_clock
                                     // , const HighsInt thread_id
) {
  if (!analyse_mip_time) return;
  // assert(analyse_mip_time);
  mip_clocks.timer_pointer_->start(mip_clocks.clock_[mip_clock]);
}

void HighsMipAnalysis::mipTimerStop(const HighsInt mip_clock
                                    // , const HighsInt thread_id
) {
  if (!analyse_mip_time) return;
  // assert(analyse_mip_time);
  mip_clocks.timer_pointer_->stop(mip_clocks.clock_[mip_clock]);
}

void HighsMipAnalysis::reportMipTimer() {
  if (!analyse_mip_time) return;
  //  assert(analyse_mip_time);
  MipTimer mip_timer;
  mip_timer.reportMipCoreClock(mip_clocks);
}
