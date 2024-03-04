use core::fmt;

use super::weather_server_record::{SkyCoverage, WeatherServerRecord};
use serde::Serialize;

const NO_COVERAGE: u16 = 32000;
const UNRESTRICTED_VISIBILITY: u16 = 10;

const LOW_IFR_CEILING: u16 = 500;
const LOW_IFR_VISIBILITY: u16 = 1;

const IFR_CEILING: u16 = 1000;
const IFR_VISIBILITY: u16 = 3;

const MARGINAL_VFR_CEILING: u16 = 3000;
const MARGINAL_VFR_VISIBILITY: u16 = 5;

#[derive(Serialize)]
pub enum WeatherCategory {
    VFR,
    MVFR,
    IFR,
    LIFR,
    Unknown,
}

impl fmt::Display for WeatherCategory {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            WeatherCategory::VFR => write!(f, "VFR"),
            WeatherCategory::MVFR => write!(f, "MVFR"),
            WeatherCategory::IFR => write!(f, "IFR"),
            WeatherCategory::LIFR => write!(f, "LIFR"),
            WeatherCategory::Unknown => write!(f, "Unknown"),
        }
    }
}

fn determine_weather_category(weather_record: &WeatherServerRecord) -> WeatherCategory {
    let lowest_cloud_layer = weather_record
        .sky_coverage
        .iter()
        .filter(|layer| {
            layer.coverage_type == SkyCoverage::Broken
                || layer.coverage_type == SkyCoverage::Overcast
                || layer.coverage_type == SkyCoverage::Obscured
        })
        .min_by(|x, y| x.bases_altitude.cmp(&y.bases_altitude));

    let visibility_value = if let Some(visibility) = &weather_record.visibility {
        match visibility {
            super::weather_server_record::WeatherServerVisibility::Specific(value) => {
                value.round() as u16
            }
            super::weather_server_record::WeatherServerVisibility::Unrestricted(_) => {
                UNRESTRICTED_VISIBILITY
            }
        }
    } else {
        return WeatherCategory::Unknown;
    };

    let bases = if let Some(lowest_bases) = lowest_cloud_layer {
        if let Some(bases_value) = lowest_bases.bases_altitude {
            bases_value
        } else {
            return WeatherCategory::Unknown;
        }
    } else {
        NO_COVERAGE
    };

    if bases < LOW_IFR_CEILING || visibility_value < LOW_IFR_VISIBILITY {
        return WeatherCategory::LIFR;
    }

    if bases < IFR_CEILING || visibility_value < IFR_VISIBILITY {
        return WeatherCategory::IFR;
    }

    if bases < MARGINAL_VFR_CEILING || visibility_value < MARGINAL_VFR_VISIBILITY {
        return WeatherCategory::MVFR;
    }

    WeatherCategory::VFR
}

#[derive(Serialize)]
pub struct WeatherCategoryData {
    pub station_id: String,
    pub weather_category: WeatherCategory,
}

impl From<&WeatherServerRecord> for WeatherCategoryData {
    fn from(value: &WeatherServerRecord) -> Self {
        WeatherCategoryData {
            station_id: value.station_id.clone(),
            weather_category: determine_weather_category(value),
        }
    }
}
